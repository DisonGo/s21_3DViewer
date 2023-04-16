#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QWidget>
#include "camera.h"
#include <QAbstractButton>

namespace Ui {
class CameraWidget;
}

class CameraWidget : public QWidget
{
  Q_OBJECT

public:
  explicit CameraWidget(QWidget *parent = nullptr);
  CameraWidget(Camera* camera, QWidget *parent = nullptr);
  ~CameraWidget();
  void SetCamera(Camera* camera);


private slots:
  void on_ResetBut_clicked();
  void SetValuesFromConfig(const Camera::CameraConfig& config);
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
  Camera::CameraConfig config;
  Camera *camera = nullptr;
  Ui::CameraWidget *ui;
};

#endif // CAMERAWIDGET_H
