#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setUnifiedTitleAndToolBarOnMac(true);
    connect(ui->toolButton_tab1, SIGNAL(clicked()), this, SLOT(choose_file()));
    connect(ui->pushButton_colorLine, SIGNAL(clicked()), this, SLOT(choose_color()));
    connect(ui->pushButton_colorVersh, SIGNAL(clicked()), this, SLOT(choose_color()));
    connect(ui->pushButton_backgroungColor, SIGNAL(clicked()), this, SLOT(choose_color()));
    connect(ui->PointType, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(updateCircleType(QAbstractButton*)));
    connect(ui->CameraMode, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(setCameraMode(QAbstractButton*)));
    connect(ui->LinePattern, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(setLinePattern(QAbstractButton*)));
    connect(ui->zNear_i, SIGNAL(valueChanged(double)), this, SLOT(updateZPlane(double)));
    connect(ui->zFar_i, SIGNAL(valueChanged(double)), this, SLOT(updateZPlane(double)));
}

MainWindow::~MainWindow()
{
    delete ui;
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
    ui->comboBox_tab1->addItem(filename);
    ui->comboBox_tab1->setCurrentIndex(ui->comboBox_tab1->findText(filename));

}
void MainWindow::updateZPlane(double value) {
  QDoubleSpinBox* caller = (QDoubleSpinBox*) sender();
  if (caller == ui->zNear_i)
    ui->openGLWidget->cameraConf.zRange.setX(value);
  else if (caller == ui->zFar_i)
    ui->openGLWidget->cameraConf.zRange.setY(value);
  else return;
  ui->openGLWidget->update();
}
void MainWindow::choose_color(){
  QPushButton* caller = (QPushButton*) sender();
  QColor color = QColorDialog::getColor(Qt::red, this);
  if (caller == ui->pushButton_colorLine)
    ui->openGLWidget->LineColor = color;
  if (caller == ui->pushButton_colorVersh)
    ui->openGLWidget->DotColor = color;
  if (caller == ui->pushButton_backgroungColor)
    ui->openGLWidget->BackColor = color;
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
  if (but == ui->radioButton_typeParallel)
    ui->openGLWidget->camera->setViewMode(Camera::Orthographic);
  else if (but == ui->radioButton_typeCentr)
    ui->openGLWidget->camera->setViewMode(Camera::Perspective);
  ui->openGLWidget->update();
}

void MainWindow::on_pushButton_loadFile_clicked()
{
    QString filePath = ui->comboBox_tab1->currentText();
    if (filePath == "") return;
    ui->openGLWidget->importObjFile(filePath);
}


void MainWindow::on_doubleSpinBox_widthLine_valueChanged(double arg1)
{
  if (arg1 > 0)
    ui->openGLWidget->drawArrConf.Lines = true;
  else
    ui->openGLWidget->drawArrConf.Lines = false;
  ui->openGLWidget->setLineWidth(arg1);
}


void MainWindow::on_doubleSpinBox_widthTop_valueChanged(double arg1)
{
  ui->openGLWidget->drawArrConf.Point_size = arg1;
  ui->openGLWidget->update();
}
void MainWindow::updateCircleType(QAbstractButton* but) {
  ui->openGLWidget->drawArrConf.Points = true;
  if (but == ui->radioButton_topCircle)
    ui->openGLWidget->drawArrConf.roundCircle = true;
  else if (but == ui->radioButton_topSquear)
    ui->openGLWidget->drawArrConf.roundCircle = false;
  else {
    ui->openGLWidget->drawArrConf.roundCircle = false;
    ui->openGLWidget->drawArrConf.Points = false;
  }
  ui->openGLWidget->update();
}

void MainWindow::on_doubleSpinBox_scale_valueChanged(double arg1)
{
  ui->openGLWidget->setScale(arg1);
}


void MainWindow::on_doubleSpinBox_moveX_valueChanged(double arg1)
{
  translation.setX(arg1);
  ui->openGLWidget->setTranslation(translation);
}


void MainWindow::on_doubleSpinBox_moveY_valueChanged(double arg1)
{
  translation.setY(arg1);
  ui->openGLWidget->setTranslation(translation);
}


void MainWindow::on_doubleSpinBox_moveZ_valueChanged(double arg1)
{
  translation.setZ(arg1);
  ui->openGLWidget->setTranslation(translation);
}


void MainWindow::on_doubleSpinBox_rotateX_valueChanged(double arg1)
{
  rotation.setX(arg1);
  ui->openGLWidget->setRotation(rotation);
}
void MainWindow::on_doubleSpinBox_rotateY_valueChanged(double arg1)
{
  rotation.setY(arg1);
  ui->openGLWidget->setRotation(rotation);
}
void MainWindow::on_doubleSpinBox_rotateZ_valueChanged(double arg1)
{
  rotation.setZ(arg1);
  ui->openGLWidget->setRotation(rotation);
}

