#include "mainwindow.h"
#include "./ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  ui->cam_focus_x_i->setValidator(new QDoubleValidator(-1e+7, 1e+7, 6, this));
  ui->cam_focus_y_i->setValidator(new QDoubleValidator(-1e+7, 1e+7, 6, this));
  ui->cam_focus_z_i->setValidator(new QDoubleValidator(-1e+7, 1e+7, 6, this));

  ui->cam_pos_x_i->setValidator(new QDoubleValidator(-1e+7, 1e+7, 6, this));
  ui->cam_pos_y_i->setValidator(new QDoubleValidator(-1e+7, 1e+7, 6, this));
  ui->cam_pos_z_i->setValidator(new QDoubleValidator(-1e+7, 1e+7, 6, this));

  ui->cam_z_near_i->setValidator(new QDoubleValidator(-1e+7, 1e+7, 6, this));
  ui->cam_z_far_i->setValidator(new QDoubleValidator(-1e+7, 1e+7, 6, this));
  ui->cam_fov_i->setValidator(new QIntValidator(1, 360, this));

  connect(ui->cam_focus_x_i, SIGNAL(editingFinished()), this, SLOT(updateCameraConf()));
  connect(ui->cam_focus_y_i, SIGNAL(editingFinished()), this, SLOT(updateCameraConf()));
  connect(ui->cam_focus_z_i, SIGNAL(editingFinished()), this, SLOT(updateCameraConf()));

  connect(ui->cam_pos_x_i, SIGNAL(editingFinished()), this, SLOT(updateCameraConf()));
  connect(ui->cam_pos_y_i, SIGNAL(editingFinished()), this, SLOT(updateCameraConf()));
  connect(ui->cam_pos_z_i, SIGNAL(editingFinished()), this, SLOT(updateCameraConf()));

  connect(ui->cam_mode_focus_but, SIGNAL(clicked(bool)), this, SLOT(updateCameraConf()));
  connect(ui->cam_mode_free_but, SIGNAL(clicked(bool)), this, SLOT(updateCameraConf()));

  connect(ui->cam_fov_i, SIGNAL(editingFinished()), this, SLOT(updateCameraConf()));

  connect(ui->cam_z_near_i, SIGNAL(editingFinished()), this, SLOT(updateCameraConf()));
  connect(ui->cam_z_far_i, SIGNAL(editingFinished()), this, SLOT(updateCameraConf()));
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::updateLabels(CameraData data)
{
  QString centerPoint = QString("(%1\n%2)").arg(data.centerPoint.rx()).arg(data.centerPoint.ry());
  QString relPoint = QString("(%1\n%2)").arg(data.relevantPoint.rx()).arg(data.relevantPoint.ry());
  QString rotX = QString("%1").arg(data.rotX);
  QString rotY = QString("%1").arg(data.rotY);
  QString angle = QString("%1").arg(data.angle);
  QString speed = QString("%1").arg(data.speed);
  QString orientation = QString("(%1\n%2\n%3)").arg(data.orientation.x()).arg(data.orientation.y()).arg(data.orientation.z());
  QString position = QString("(%1\n%2\n%3)").arg(data.position.x()).arg(data.position.y()).arg(data.position.z());

  ui->camera_center_point_data->setText(centerPoint);
  ui->camera_rel_point_data->setText(relPoint);
  ui->camera_rot_x_data->setText(rotX);
  ui->camera_rot_y_data->setText(rotY);
  ui->camera_angle_data->setText(angle);
  ui->camera_speed_data->setText(speed);
  ui->camera_orientation_data->setText(orientation);
  ui->camera_pos_data->setText(position);
}

void MainWindow::updateArrConf()
{
  ui->openGLWidget->setDrawArrConfig(arrConf);
}

void MainWindow::updateElementsConf()
{
  ui->openGLWidget->setDrawElemConfig(elemConf);
}

void MainWindow::updateCameraConf()
{
  QVector3D Pos, FocusPoint;
  float FOV;
  camConf.Mode = ui->Camera_mode->checkedId() == -2 ? Camera::Free : Camera::Focus;
//  qDebug() << ui->Camera_mode->checkedId();
  camConf.FocusPoint.setX(ui->cam_focus_x_i->text().toFloat());
  camConf.FocusPoint.setY(ui->cam_focus_y_i->text().toFloat());
  camConf.FocusPoint.setZ(ui->cam_focus_z_i->text().toFloat());

  camConf.FOV = ui->cam_fov_i->text().toFloat();

  camConf.Position.setX(ui->cam_pos_x_i->text().toFloat());
  camConf.Position.setY(ui->cam_pos_y_i->text().toFloat());
  camConf.Position.setZ(ui->cam_pos_z_i->text().toFloat());

  camConf.zRange.setX(ui->cam_z_near_i->text().toFloat());
  camConf.zRange.setY(ui->cam_z_far_i->text().toFloat());

  ui->openGLWidget->setCameraConfig(camConf);
}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
  elemConf.Points = arg1;
  updateElementsConf();
}
void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
  elemConf.Lines = arg1;
  updateElementsConf();
}
void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
  elemConf.Triangles = arg1;
  updateElementsConf();
}
void MainWindow::on_checkBox_4_stateChanged(int arg1)
{
  elemConf.Triangles_strip = arg1;
  updateElementsConf();
}
void MainWindow::on_checkBox_5_stateChanged(int arg1)
{
  arrConf.Points = arg1;
  updateArrConf();
}
void MainWindow::on_checkBox_6_stateChanged(int arg1)
{
  arrConf.Lines = arg1;
  updateArrConf();

}
void MainWindow::on_checkBox_7_stateChanged(int arg1)
{
  arrConf.Triangles = arg1;
  updateArrConf();
}
void MainWindow::on_checkBox_8_stateChanged(int arg1)
{
  arrConf.Triangles_strip = arg1;
  updateArrConf();
}
