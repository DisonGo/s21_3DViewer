#include "FileImportWidget.h"

#include "ui_FileImportWidget.h"
#include <QFileDialog>
#include <QFileInfo>
namespace s21 {
FileImportWidget::FileImportWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::FileImportWidget) {
  Setup();
}

FileImportWidget::~FileImportWidget() { delete ui; }

void FileImportWidget::ImportPaths(QVector<QString> paths)
{
  ImportPaths((std::vector<QString>){paths.begin(), paths.end()});
}

void FileImportWidget::ImportPaths(std::vector<QString> paths)
{
  std::vector<std::string> new_paths;
  for (const auto& path : paths)
    new_paths.push_back(path.toStdString());
  ImportPaths(new_paths);
}

void FileImportWidget::ImportPaths(std::vector<std::string> paths)
{
  for (const auto& path : paths) {
    const auto str = path.c_str();
    if (!QFileInfo::exists(str)) continue;
    file_paths_ << str;
    ui->FileListCB->addItem(str);
  }
}

std::vector<std::string> FileImportWidget::ExportPaths()

{
  return PathsToStdVector();
}

QVector<QString> FileImportWidget::ExportPathsQ()
{

  return file_paths_;
}

void FileImportWidget::Setup()
{
  ui->setupUi(this);
  connect(ui->OpenFileBut, &QAbstractButton::clicked, this, &FileImportWidget::ChooseFile);
  connect(ui->LoadFileBut, &QAbstractButton::clicked, this, &FileImportWidget::ImportFile);
}

void FileImportWidget::ChooseFile() {
  QString name = qgetenv("USER");
  if (name.isEmpty()) name = qgetenv("USERNAME");
  QString filename = QFileDialog::getOpenFileName(
      this, tr("Open File"), "/Users/" + name, "Objects (*.obj)");
  if (filename.isEmpty()) return;
  file_paths_ << filename;
  ui->FileListCB->addItem(filename);
  ui->FileListCB->setCurrentIndex(ui->FileListCB->findText(filename));
}

void FileImportWidget::ImportFile()
{
  QString file_path = ui->FileListCB->currentText();
  if (file_path.isEmpty()) return;
  emit FileImporting(file_path);
}

std::vector<std::string> FileImportWidget::PathsToStdVector()
{
  std::vector<std::string> new_paths;
    for (const auto& path : file_paths_)
      new_paths.push_back(path.toStdString());
  return new_paths;
}
}
