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
#include "Logger.h"
namespace s21 {
MainWindow::MainWindow(EngineSpacer& engine_spacer,
                       DrawConfigSpacer& draw_config_spacer,
                       ImageSaverControler& image_saver_controler,
                       QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      engine_spacer_(engine_spacer),
      draw_config_spacer_(draw_config_spacer),
      image_saver_controler_(image_saver_controler) {
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
  open_gl_widget_ = new OGLWidget(engine_spacer_, splitter_);

  object_tree_ = new QTreeView(splitter_);
  object_tree_->setMinimumWidth(200);
  object_tree_->setMaximumWidth(300);
  object_tree_->resize(300, 720);
  object_tree_->header()->setFixedHeight(30);

  splitter_->addWidget(object_tree_);
  splitter_->addWidget(open_gl_widget_);
  splitter_->resize(1280, 720);

  splitter_->setFocusPolicy(Qt::NoFocus);
  open_gl_widget_->setFocusPolicy(Qt::StrongFocus);
  ui->mainBackLayout->addWidget(splitter_);
  splitter_->show();
  ui->object_stats_l_wid->move(object_tree_->width() + 7,
                               ui->object_stats_l_wid->y());
  connect(ui->FileImporter, SIGNAL(FileImporting(QString)), this,
          SLOT(ImportFile(QString)));
  connect(open_gl_widget_, SIGNAL(Initialized()), this,
          SLOT(SetupEObjectTreeView()));
  connect(ui->background_color_b, SIGNAL(clicked()), this,
          SLOT(ChooseBackColor()));
  connect(ui->record_b, SIGNAL(clicked()), this, SLOT(StartRecord()));
  connect(ui->screenshot_b, SIGNAL(clicked()), this, SLOT(SaveScreenshot()));
  connect(&engine_spacer_, &EngineSpacer::ObjectImported, this,
          &MainWindow::PrintImported);
  connect(ui->unload_texture_b, &QPushButton::pressed, &engine_spacer_,
          &EngineSpacer::UnloadTexture);
  connect(ui->select_texture_b, &QPushButton::pressed, this,
          &MainWindow::SelectTexture);
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
  //  if (!QFileInfo::exists(path)) {
  //    QErrorMessage* errorMessage = new QErrorMessage();
  //    errorMessage->setWindowTitle("Import error");
  //    errorMessage->showMessage("Choosen file doesn't exist");
  //    errorMessage->exec();
  //    return;
  //  }
  open_gl_widget_->makeCurrent();
  engine_spacer_.ImportOBJFile(path.toStdString());
  clearLayout(ui->ObjectWidgetHolder);
  ui->ObjectWidgetHolderWidget->resize(
      ui->ObjectWidgetHolderWidget->size().width(), 0);
  open_gl_widget_->SetCameraSpacer(nullptr);
  UpdateGL();
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
  auto log = std::string("Creating widget of type ") +
             std::to_string(object->GetType());
  logger_.Log(log);
  ConfigWidget* widget = widget_factory.CreateWidget(object, this);
  CameraSpacer* cam_spacer = nullptr;
  if (!widget) {
    logger_.Log("Widget is null. Aborting.");
    return;
  };
  if (object->GetType() == kCamera)
    cam_spacer = static_cast<CameraConfigView*>(widget)->GetCameraSpacer();
  open_gl_widget_->SetCameraSpacer(cam_spacer);

  connect(widget, SIGNAL(UpdateRequest()), this, SLOT(UpdateGL()));

  ui->ObjectWidgetHolderWidget->resize(
      ui->ObjectWidgetHolderWidget->size().width(), widget->size().height());
  ui->ObjectWidgetHolder->addWidget(widget);
}

void MainWindow::StartRecord() {
  open_gl_widget_->StartScreenCapture(gif_fps_, gif_length_);
  QTimer::singleShot(gif_length_ * 1000, this, &MainWindow::StopRecord);
}

void MainWindow::StopRecord() {
  auto gif_data = open_gl_widget_->StopScreenCapture();
  image_saver_controler_.SaveGif(gif_data, gif_resolution_, gif_fps_);
}

void MainWindow::SaveScreenshot() {
  image_saver_controler_.SaveScreenShot(open_gl_widget_->GetScreenShot());
}

void MainWindow::SetupEObjectTreeView() {
  auto eObjectModel = &engine_spacer_.GetEObjectItemModel();
  connect(object_tree_, &QAbstractItemView::clicked, eObjectModel,
          &EObjectItemModel::FindAndSelectIndex);

  connect(eObjectModel, &EObjectItemModel::ObjectSelected, this,
          &MainWindow::ShowObjectWidget);
  object_tree_->setModel(eObjectModel);
}

void MainWindow::SelectTexture() {
  QString name = qgetenv("USER");
  if (name.isEmpty()) name = qgetenv("USERNAME");
  QString filename = QFileDialog::getOpenFileName(
      this, tr("Open File"), "/Users/" + name,
      "BMP Files (*.bmp);;JPEG Files (*.jp*g);;PNG Files(*.png)");
  if (filename.isEmpty()) return;
  engine_spacer_.ImportTextureFile(filename.toStdString());
}

void MainWindow::PrintImported(unsigned long vertices_n,
                               unsigned long indices_n, std::string file_name) {
  ui->object_vertices_label->setText(QString("Vertices: %1").arg(vertices_n));
  ui->object_edges_label->setText(QString("Edges: %1").arg(indices_n / 4));
  ui->object_name_label->setText(
      QString("File name: %1").arg(file_name.c_str()));
}

void MainWindow::UpdateGL() { open_gl_widget_->update(); }
}  // namespace s21
