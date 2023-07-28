#include "MainWindow.h"

#include <FileImportWidget.h>
#include <qgifimage.h>

#include <QColorDialog>
#include <QErrorMessage>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QHeaderView>
#include <QImageWriter>
#include <QMessageBox>
#include <QVariantAnimation>

#include "./ui_mainwindow.h"
namespace s21 {
MainWindow::MainWindow(EngineSpacer& engine_spacer,
                       DrawConfigSpacer& draw_config_spacer, QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      engine_spacer_(engine_spacer),
      draw_config_spacer_(draw_config_spacer) {
  Setup();
  LoadSettings();
}
MainWindow::~MainWindow() { delete ui; }
void MainWindow::closeEvent(QCloseEvent* event) {
  Q_UNUSED(event)
  SaveSettings();
}
void MainWindow::SaveSettings() {
  settings_.beginGroup("Settings");

  settings_.beginWriteArray("file_paths");
  int i = 0;
  for (auto& file_path : ui->FileImporter->ExportPathsQ()) {
    settings_.setArrayIndex(i++);
    settings_.setValue("path", file_path);
  }
  settings_.endArray();
  settings_.setValue("back_color", draw_config_spacer_.GetBackColor());
  settings_.endGroup();
}

void MainWindow::Setup() {
  ui->setupUi(this);
  setUnifiedTitleAndToolBarOnMac(true);
  SetupView();
}

void MainWindow::SetupView() {
  splitter_ = new QSplitter(this);
  openGLWidget = new OGLWidget(engine_spacer_, splitter_);

  object_tree = new QTreeView(splitter_);
  object_tree->setMinimumWidth(200);
  object_tree->setMaximumWidth(300);
  object_tree->header()->setFixedHeight(30);

  splitter_->addWidget(object_tree);
  splitter_->addWidget(openGLWidget);
  splitter_->resize(1280, 720);

  splitter_->setFocusPolicy(Qt::NoFocus);
  openGLWidget->setFocusPolicy(Qt::StrongFocus);
  ui->mainBackLayout->addWidget(splitter_);

  connect(ui->FileImporter, SIGNAL(FileImporting(QString)), this,
          SLOT(ImportFile(QString)));
  connect(openGLWidget, SIGNAL(Initialized()), this,
          SLOT(SetupEObjectTreeView()));
  connect(ui->background_color_b, SIGNAL(clicked()), this,
          SLOT(ChooseBackColor()));
  connect(ui->record_b, SIGNAL(clicked()), this, SLOT(StartRecord()));
}

void MainWindow::LoadSettings() {
  settings_.beginGroup("Settings");
  int size = settings_.beginReadArray("file_paths");
  std::vector<QString> paths;
  for (int i = 0; i < size; i++) {
    settings_.setArrayIndex(i);
    paths.push_back(settings_.value("path").value<QString>());
  }
  settings_.endArray();
  QColor back_color;
  if (settings_.contains("back_color"))
    back_color = settings_.value("back_color").value<QColor>();
  else
    back_color = draw_config_spacer_.GetBackColor();
  settings_.endGroup();
  ui->FileImporter->ImportPaths(paths);
  draw_config_spacer_.SetBackColor(back_color);
}
void clearLayout(QLayout* layout, bool deleteWidgets = true) {
  while (QLayoutItem* item = layout->takeAt(0)) {
    if (deleteWidgets) {
      if (QWidget* widget = item->widget()) widget->close();
    }
    if (QLayout* childLayout = item->layout())
      clearLayout(childLayout, deleteWidgets);
    delete item;
  }
}
void MainWindow::ImportFile(QString path) {
  if (!QFileInfo::exists(path)) {
    QErrorMessage* errorMessage = new QErrorMessage();
    errorMessage->setWindowTitle("Import error");
    errorMessage->showMessage("Choosen file doesn't exist");
    errorMessage->exec();
    return;
  }
  openGLWidget->makeCurrent();
  engine_spacer_.ImportOBJFile(path.toStdString());
  clearLayout(ui->ObjectWidgetHolder);
  ui->verticalWidget_2->resize(ui->verticalWidget_2->size().width(), 0);
  openGLWidget->SetCameraSpacer(nullptr);
  openGLWidget->update();
}

void MainWindow::ChooseBackColor() {
  auto color = QColorDialog::getColor(draw_config_spacer_.GetBackColor(), this,
                                      "Background color");
  draw_config_spacer_.SetBackColor(color);
  UpdateGL();
}

void MainWindow::ShowObjectWidget(EObject* object) {
  static ConfigWidgetFactory widget_factory;
  clearLayout(ui->ObjectWidgetHolder);
  ConfigWidget* widget = widget_factory.CreateWidget(object, this);
  CameraSpacer* cam_spacer = nullptr;
  if (!widget) return;
  if (object->GetType() == kCamera)
    cam_spacer = static_cast<CameraConfigView*>(widget)->GetCameraSpacer();
  openGLWidget->SetCameraSpacer(cam_spacer);

  connect(widget, SIGNAL(UpdateRequest()), this, SLOT(UpdateGL()));
  ui->verticalWidget_2->resize(ui->verticalWidget_2->size().width(),
                               widget->size().height());
  ui->ObjectWidgetHolder->addWidget(widget);
}

void MainWindow::StartRecord()
{
  openGLWidget->StartScreenCapture(git_fps_);
  QTimer::singleShot(5000, this,  &MainWindow::StopRecord);
}

void MainWindow::StopRecord()
{
  auto data = openGLWidget->StopScreenCapture();
  SaveGif(data, git_fps_);
}

void MainWindow::SetupEObjectTreeView() {
  auto eObjectModel = &engine_spacer_.GetEObjectItemModel();
  connect(object_tree, &QAbstractItemView::clicked, eObjectModel,
          &EObjectItemModel::FindAndSelectIndex);

  connect(eObjectModel, &EObjectItemModel::ObjectSelected, this,
          &MainWindow::ShowObjectWidget);
  object_tree->setModel(eObjectModel);
}
void MainWindow::SaveGif(std::vector<QImage> gifData, unsigned FPS) {
  QGifImage gif(QSize(640, 480));
  qDebug()  << "Frames count:" << gifData.size();
  qDebug()  << "Fps determined for 5 seconds:" << gifData.size()/5;
  gif.setDefaultDelay(1000 / FPS);
  for (auto& frame : gifData) {
    gif.addFrame(frame);
  }
  QString name = qgetenv("USER");
  if (name.isEmpty()) name = qgetenv("USERNAME");
  QString savePath = QFileDialog::getSaveFileName(
      this, tr("Save gif"), "/Users/" + name, "Image (*.gif)");
  gif.save(savePath);
}
void MainWindow::UpdateGL() { openGLWidget->update(); }
}  // namespace s21
