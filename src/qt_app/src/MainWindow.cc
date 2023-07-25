#include "MainWindow.h"

#include <qgifimage.h>

#include <QColorDialog>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QImageWriter>
#include <QMessageBox>
#include <QVariantAnimation>
#include <FileImportWidget.h>
#include <QHeaderView>
#include "./ui_mainwindow.h"
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setUnifiedTitleAndToolBarOnMac(true);
  loadSettings();
  applySettings();

  splitter_ = new QSplitter(this);
  openGLWidget = new OpenGLController(splitter_);
  openGLWidget->setFocusPolicy(Qt::StrongFocus);
  object_tree = new QTreeView(splitter_);
  object_tree->setMinimumWidth(200);
  object_tree->setMaximumWidth(300);
  auto header = object_tree->header();
  header->setFixedHeight(30);
  connect(ui->FileImporter, SIGNAL(FileImporting(QString)), this, SLOT(ImportFile(QString)));
  connect(openGLWidget, SIGNAL(initialized()), this,
          SLOT(SetupEObjectTreeView()));
  splitter_->addWidget(object_tree);
  splitter_->addWidget(openGLWidget);
  splitter_->resize(1280, 720);
  splitter_->setFocusPolicy(Qt::NoFocus);
  ui->mainBackLayout->addWidget(splitter_);
//  QVBoxLayout* mainLayout = new QVBoxLayout(this);

//  // Add the new widget to the layout
//  mainLayout->addWidget(splitter_);
//  setAttribute(Qt::WA_NoSystemBackground);
}
MainWindow::~MainWindow() { delete ui; }
void MainWindow::closeEvent(QCloseEvent* event) {
  Q_UNUSED(event)
  saveSettings();
}
void MainWindow::saveSettings() {
  QSettings settings("settings.ini", QSettings::IniFormat);
  settings.beginGroup("Settings");

  settings.beginWriteArray("filePaths");
  int i = 0;
  for (auto& filePath : ui->FileImporter->ExportPathsQ()) {
    settings.setArrayIndex(i++);
    settings.setValue("path", filePath);
  }
  settings.endArray();
  settings.endGroup();
}

void MainWindow::loadSettings() {
  if (QFile::exists("settings.ini")) {
    QSettings settings("settings.ini", QSettings::IniFormat);
    settings.beginGroup("Settings");
    int size = settings.beginReadArray("filePaths");
    for (int i = 0; i < size; i++) {
      settings.setArrayIndex(i);
      filePaths.push_back(settings.value("path").value<QString>());
    }
    settings.endArray();
    settings.endGroup();
  }
}
void MainWindow::applySettings() {
  ui->FileImporter->ImportPaths(filePaths);
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
  openGLWidget->importObjFile(path);
  clearLayout(ui->ObjectWidgetHolder);
  ui->verticalWidget_2->resize(ui->verticalWidget_2->size().width(), 0);
  openGLWidget->SetCameraSpacer(nullptr);
}

void MainWindow::ShowObjectWidget(s21::EObject* object) {
  static ConfigWidgetFactory widget_factory;
  clearLayout(ui->ObjectWidgetHolder);
  ConfigWidget* widget = widget_factory.CreateWidget(object, this);
  s21::CameraSpacer* cam_spacer = nullptr;
  if (!widget) return;
  if (object->GetType() == s21::kCamera)
    cam_spacer = static_cast<CameraConfigView*>(widget)->GetCameraSpacer();
  openGLWidget->SetCameraSpacer(cam_spacer);

  connect(widget, SIGNAL(UpdateRequest()), this, SLOT(UpdateGL()));
  ui->verticalWidget_2->resize(ui->verticalWidget_2->size().width(), widget->size().height());
  ui->ObjectWidgetHolder->addWidget(widget);
}

void MainWindow::SetupEObjectTreeView() {
  auto eObjectModel = &s21::Engine::Instance().GetEObjectItemModel();
  connect(object_tree, &QAbstractItemView::clicked, eObjectModel,
          &s21::EObjectItemModel::FindAndSelectIndex);

  connect(eObjectModel, &s21::EObjectItemModel::ObjectSelected, this,
          &MainWindow::ShowObjectWidget);
  object_tree->setModel(eObjectModel);
}

void MainWindow::UpdateGL() { openGLWidget->update(); }
