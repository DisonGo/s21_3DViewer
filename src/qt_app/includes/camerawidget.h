#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QWidget>
#include "Spacers/CameraSpacer.h"
#include <QAbstractButton>

namespace Ui {
class CameraWidget;
}

class CameraWidget : public QWidget
{
  Q_OBJECT

public:
  explicit CameraWidget(QWidget *parent = nullptr, CameraSpacer* cameraSpacer = nullptr);
  ~CameraWidget();


    void SetCameraSpacer(CameraSpacer *cameraSpacer);
private slots:
//  void on_ResetBut_clicked();
  void SetConfig(Camera::CameraConfig* config);
  void SetValuesFromConfig();
  void SetPosition(const QVector3D&);
  void SetOrientation(const QVector3D&);
  void SetFocusPoint(const QVector3D&);
  void SetCameraMode(QAbstractButton*);
  void SetViewMode(QAbstractButton*);
  void SetZNear(double);
  void SetZFar(double);
  void SetBoxLeft(double);
  void SetBoxRight(double);
  void SetBoxBottom(double);
  void SetBoxTop(double);


private:
  void SetupConnects();
  CameraSpacer* cameraSpacer_{};
  Camera::CameraConfig* config_{};
  Ui::CameraWidget *ui;
};

#endif // CAMERAWIDGET_H
