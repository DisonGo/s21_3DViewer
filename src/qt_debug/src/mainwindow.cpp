#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
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

