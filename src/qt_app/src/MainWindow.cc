#include "MainWindow.h"

#include <FileImportWidget.h>
#include <qgifimage.h>

#include <QColorDialog>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QHeaderView>
#include <QImageWriter>
#include <QMessageBox>
#include <QVariantAnimation>

#include "./ui_mainwindow.h"
namespace s21 {
MainWindow::MainWindow(EngineSpacer& engine_spacer, QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      engine_spacer_(engine_spacer) {
  Setup();
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

void MainWindow::Setup()
{
  ui->setupUi(this);
  setUnifiedTitleAndToolBarOnMac(true);
  SetupView();
}

void MainWindow::SetupView()
{
  splitter_ = new QSplitter(this);
  openGLWidget = new OpenGLController(engine_spacer_, splitter_);

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
void MainWindow::applySettings() { ui->FileImporter->ImportPaths(filePaths); }
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
  openGLWidget->makeCurrent();
  engine_spacer_.ImportOBJFile(path.toStdString());
  clearLayout(ui->ObjectWidgetHolder);
  ui->verticalWidget_2->resize(ui->verticalWidget_2->size().width(), 0);
  openGLWidget->SetCameraSpacer(nullptr);
  openGLWidget->update();
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

void MainWindow::SetupEObjectTreeView() {
  auto eObjectModel = &engine_spacer_.GetEObjectItemModel();
  connect(object_tree, &QAbstractItemView::clicked, eObjectModel,
          &EObjectItemModel::FindAndSelectIndex);

  connect(eObjectModel, &EObjectItemModel::ObjectSelected, this,
          &MainWindow::ShowObjectWidget);
  object_tree->setModel(eObjectModel);
}

void MainWindow::UpdateGL() { openGLWidget->update(); }
}
