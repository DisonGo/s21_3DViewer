#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "openglcontroller.h"
#include "camera.h"
extern "C" {
#include "obj_parser.h"
}
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  OpenGLController::glDrawArraysConfig arrConf;
  OpenGLController::glDrawElementsConfig elemConf;
  OpenGLController::cameraConfig camConf;
private slots:
   void updateLabels(CameraData data);
   void updateArrConf();
   void updateElementsConf();
   void updateCameraConf();
   void on_checkBox_stateChanged(int arg1);
   void on_checkBox_2_stateChanged(int arg1);
   void on_checkBox_3_stateChanged(int arg1);
   void on_checkBox_4_stateChanged(int arg1);
   void on_checkBox_5_stateChanged(int arg1);
   void on_checkBox_6_stateChanged(int arg1);
   void on_checkBox_7_stateChanged(int arg1);
   void on_checkBox_8_stateChanged(int arg1);
};
#endif // MAINWINDOW_H
