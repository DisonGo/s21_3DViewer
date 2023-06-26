#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QColorDialog>
#include <QImageWriter>
#include <QVariantAnimation>
#include <qgifimage.h>
#include <ObjParser.h>
#include <QFileSystemModel>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  setUnifiedTitleAndToolBarOnMac(true);
  loadSettings();
  applySettings();
  connect(ui->openGLWidget, SIGNAL(initialized()), this, SLOT(SetupCameraWid()));
  connect(ui->toolButton_tab1, SIGNAL(clicked()), this, SLOT(choose_file()));
  connect(ui->pushButton_colorLine, SIGNAL(clicked()), this, SLOT(choose_color()));
  connect(ui->pushButton_colorVersh, SIGNAL(clicked()), this, SLOT(choose_color()));
  connect(ui->pushButton_backgroungColor, SIGNAL(clicked()), this, SLOT(choose_color()));
  connect(ui->PointType, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(updateCircleType(QAbstractButton*)));
  connect(ui->CameraMode, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(setCameraMode(QAbstractButton*)));
  connect(ui->LinePattern, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(setLinePattern(QAbstractButton*)));
  connect(ui->zNear_i, SIGNAL(valueChanged(double)), this, SLOT(updateZPlane(double)));
  connect(ui->zFar_i, SIGNAL(valueChanged(double)), this, SLOT(updateZPlane(double)));
  connect(ui->openGLWidget, SIGNAL(importComleted(long,long,QString)), this, SLOT(updateInfoLabels(long,long,QString)));


}
void MainWindow::TranslationTest(QVector3D values) {
    qDebug() << values;
}
MainWindow::~MainWindow()
{
  delete ui;
}
void MainWindow::closeEvent(QCloseEvent *event) {
  Q_UNUSED(event)
  saveSettings();
}
void MainWindow::saveSettings() {
  QSettings settings("settings.ini",QSettings::IniFormat);
  settings.beginGroup("Settings");
  settings.setValue("translation", translation);
  settings.setValue("rotation", rotation);
  settings.setValue("lineColor", lineColor);
  settings.setValue("pointColor", pointColor);
  settings.setValue("backColor", backColor);
  settings.setValue("zRange", zRange);
  settings.setValue("lineWidth", lineWidth);
  settings.setValue("pointWidth", pointWidth);
  settings.setValue("pointTypeIndex", pointTypeIndex);
  settings.setValue("viewTypeIndex", viewTypeIndex);
  settings.setValue("fileFieldIndex", fileFieldIndex);
  settings.setValue("scale", scale);

//  settings.setValue("cameraPos", ui->openGLWidget->camera->getPosition());
//  settings.setValue("cameraOrient", ui->openGLWidget->camera->getOrientation());

  settings.beginWriteArray("filePaths");
  int i = 0;
  for (auto &filePath : filePaths) {
    settings.setArrayIndex(i++);
    settings.setValue("path", filePath);
  }
  settings.endArray();
  settings.endGroup();
}


void MainWindow::loadSettings() {
  if (QFile::exists("settings.ini")) {
    QSettings settings("settings.ini",QSettings::IniFormat);
    settings.beginGroup("Settings");
    translation = settings.value("translation").value<QVector3D>();
    rotation = settings.value("rotation").value<QVector3D>();
    lineColor = settings.value("lineColor").value<QColor>();
    pointColor = settings.value("pointColor").value<QColor>();
    backColor = settings.value("backColor").value<QColor>();
    zRange = settings.value("zRange").value<QVector2D>();
    lineWidth = settings.value("lineWidth").value<float>();
    pointWidth = settings.value("pointWidth").value<float>();
    pointTypeIndex = settings.value("pointTypeIndex").value<int>();
    viewTypeIndex = settings.value("viewTypeIndex").value<int>();
    fileFieldIndex = settings.value("fileFieldIndex").value<int>();
    scale = settings.value("scale").value<float>();

    cameraPos = settings.value("cameraPos").value<QVector3D>();
    cameraOrient = settings.value("cameraOrient").value<QVector3D>();

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
  ui->doubleSpinBox_moveX->setValue(translation.x());
  ui->doubleSpinBox_moveY->setValue(translation.y());
  ui->doubleSpinBox_moveZ->setValue(translation.z());

  ui->doubleSpinBox_rotateX->setValue(rotation.x());
  ui->doubleSpinBox_rotateY->setValue(rotation.y());
  ui->doubleSpinBox_rotateZ->setValue(rotation.z());

  ui->zNear_i->setValue(zRange.x());
  ui->zFar_i->setValue(zRange.y());

  ui->doubleSpinBox_scale->setValue(scale);

  ui->doubleSpinBox_widthLine->setValue(lineWidth);
  ui->doubleSpinBox_widthTop->setValue(pointWidth);

  if (pointTypeIndex != -1) {
    QPushButton * but = (QPushButton*)ui->PointType->button(pointTypeIndex);
    but->setChecked(true);
    updateCircleType(but);
  }
  if (viewTypeIndex != -1) {
    QPushButton * but = (QPushButton*)ui->CameraMode->button(viewTypeIndex);
    but->setChecked(true);
    setCameraMode(but);
  }
  for (auto &filePath : filePaths)
    ui->comboBox_tab1->addItem(filePath);
  if (fileFieldIndex != -1) ui->comboBox_tab1->setCurrentIndex(fileFieldIndex);

  OpenGLController* gl = ui->openGLWidget;
  gl->LineColor = lineColor;
  gl->DotColor = pointColor;
  gl->BackColor = backColor;

  gl->drawArrConf.Line_width = lineWidth;
  if (!lineWidth) gl->drawArrConf.Lines = false;
  gl->drawArrConf.Point_size = pointWidth;
  loading_setting_done = true;
}
void MainWindow::choose_file(){
  QString name = qgetenv("USER");
  if (name.isEmpty())
    name = qgetenv("USERNAME");
  QString filename = QFileDialog::getOpenFileName(
              this,
              tr("Open File"),
              "/Users/" + name,
              "Objects (*.obj)"
              );
  if (filename.isEmpty()) return;
  filePaths.push_back(filename);
  ui->comboBox_tab1->addItem(filename);
  ui->comboBox_tab1->setCurrentIndex(ui->comboBox_tab1->findText(filename));
}
void MainWindow::updateZPlane(double value) {
  QDoubleSpinBox* caller = (QDoubleSpinBox*) sender();
  if (caller == ui->zNear_i)
    zRange.setX(value);
  else if (caller == ui->zFar_i)
    zRange.setY(value);
  else return;
  ui->openGLWidget->update();
}
void MainWindow::choose_color(){
  QPushButton* caller = (QPushButton*) sender();
  if (caller == ui->pushButton_colorLine) {
    lineColor = QColorDialog::getColor(lineColor, this);
  }
  else if (caller == ui->pushButton_colorVersh) {
    pointColor = QColorDialog::getColor(pointColor, this);
  }
  else if (caller == ui->pushButton_backgroungColor) {
    backColor = QColorDialog::getColor(backColor, this);
  }
  else return;
  ui->openGLWidget->BackColor = backColor;
  ui->openGLWidget->DotColor = pointColor;
  ui->openGLWidget->LineColor = lineColor;
  ui->openGLWidget->update();
}
void MainWindow::setLinePattern(QAbstractButton* but) {
  if (but == ui->radioButton_lineDashed)
    ui->openGLWidget->drawArrConf.dashedLines = true;
  else if (but == ui->radioButton_lineSolid)
    ui->openGLWidget->drawArrConf.dashedLines = false;
  ui->openGLWidget->update();
}
void MainWindow::setCameraMode(QAbstractButton* but) {
  viewTypeIndex = ui->CameraMode->checkedId();
  ui->openGLWidget->update();
}
void clearLayout(QLayout* layout, bool deleteWidgets = true)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (deleteWidgets)
        {
            if (QWidget* widget = item->widget())
                widget->deleteLater();
        }
        if (QLayout* childLayout = item->layout())
            clearLayout(childLayout, deleteWidgets);
        delete item;
    }
}
void MainWindow::on_pushButton_loadFile_clicked()
{
  QString filePath = ui->comboBox_tab1->currentText();
  if (filePath.isEmpty()) return;
  ui->openGLWidget->importObjFile(filePath);
  std::vector<Mesh*> meshes = ui->openGLWidget->GetMeshes();
  clearLayout(ui->Transforms);
  for (auto mesh : meshes) {
    TransformWidget* wid  = new TransformWidget(this);
    ui->Transforms->addWidget(wid);
    wid->LinkMesh(mesh);
    connect(wid, SIGNAL(TransformUpdated()), this, SLOT(UpdateGL()));
  }
}

void MainWindow::on_doubleSpinBox_widthLine_valueChanged(double arg1)
{
  if (arg1 > 0)
    ui->openGLWidget->drawArrConf.Lines = true;
  else
    ui->openGLWidget->drawArrConf.Lines = false;
  lineWidth = arg1;
  ui->openGLWidget->drawArrConf.Line_width = lineWidth;
  ui->openGLWidget->update();
}


void MainWindow::on_doubleSpinBox_widthTop_valueChanged(double arg1)
{
  pointWidth = arg1;
  ui->openGLWidget->drawArrConf.Point_size = pointWidth;
  ui->openGLWidget->update();
}
void MainWindow::updateCircleType(QAbstractButton* but) {
  ui->openGLWidget->drawArrConf.Points = true;
  if (but == ui->radioButton_topCircle)
    ui->openGLWidget->drawArrConf.roundCircle = true;
  else if (but == ui->radioButton_topSquear)
    ui->openGLWidget->drawArrConf.roundCircle = false;
  else if (but == ui->radioButton_topNone){
    ui->openGLWidget->drawArrConf.roundCircle = false;
    ui->openGLWidget->drawArrConf.Points = false;
  } else return;
  pointTypeIndex = ui->PointType->checkedId();
  ui->openGLWidget->update();
}
void MainWindow::updateInfoLabels(long int vertN, long int edgesN, QString filename) {
  ui->vetices_l->setText(QString("Total vertices:%1").arg(vertN));
  ui->edges_l->setText(QString("Total edges:%1").arg(edgesN));
  ui->filename_l->setText("File name:" + filename);
}



void MainWindow::on_comboBox_tab1_currentIndexChanged(int index)
{
  if (!loading_setting_done) return;
  fileFieldIndex = index;
}


void MainWindow::on_pushButton_saveFile_clicked()
{
  QImage screenshot = ui->openGLWidget->grabFramebuffer();
  QString name = qgetenv("USER");
  if (name.isEmpty())
    name = qgetenv("USERNAME");
  QString savePath = QFileDialog::getSaveFileName(this, tr("Save screenshot"),"/Users/" + name,"Image (*.png)");
  screenshot.save(savePath, "PNG");
}

void MainWindow::saveGif(std::vector<QImage> gifData) {
  QGifImage gif(QSize(640, 480));
  gif.setDefaultDelay(1000/10);
  for (auto &frame : gifData) {
    gif.addFrame(frame);
  }
  QString name = qgetenv("USER");
  if (name.isEmpty())
    name = qgetenv("USERNAME");
  QString savePath = QFileDialog::getSaveFileName(this, tr("Save gif"),"/Users/" + name,"Image (*.gif)");
  gif.save(savePath);
}

void MainWindow::SetupCameraWid()
{
  ui->camWid->SetCameraSpacer(ui->openGLWidget->cameraSpacer);
}

void MainWindow::UpdateGL()
{
  ui->openGLWidget->update();
}
void MainWindow::endCapture() {
  gifBuffer = ui->openGLWidget->stopScreenCapture();
  timerStarted = false;
  saveGif(gifBuffer);
}
void MainWindow::on_pushButton_screencast_clicked()
{
  if (timerStarted) return;
  ui->openGLWidget->startScreenCapture(10);
  QTimer::singleShot(5000, this, &MainWindow::endCapture);
  timerStarted = true;
}
void MainWindow::on_pushButton_screencast_auto_clicked()
{
  std::vector<QImage> gifData = ui->openGLWidget->getScreencast();
  saveGif(gifData);
}

