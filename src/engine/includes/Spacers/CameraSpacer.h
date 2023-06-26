#ifndef CAMERASPACER_H
#define CAMERASPACER_H
#include <QKeyEvent>
#include <QObject>

#include "camera.h"

class CameraSpacer : public QObject {
  Q_OBJECT
 public:
  CameraSpacer(QObject *parent, Camera &camera_);
  Camera::CameraConfig& GetConfig() { return camera_.GetConfig();};
  void SetMode(Camera::CameraMode newMode);
  void SetViewMode(Camera::ViewMode newViewMode);
  void SetFocusPoint(const QVector3D &newFocusPoint);
  void SetPosition(const QVector3D &newPosition);
  void SetOrientation(const QVector3D &newOrientation);
  void SetZRange(const QVector2D &newZRange);
  void SetFOV(float newFOV);
  void SetVw(int newVw);
  void SetVh(int newVh);
  void SetMoveSpeed(float newMoveSpeed);
  void SetRotationSpeed(float newRotationSpeed);

 public slots:
  void keyPressSlot(QKeyEvent *e);
  void keyReleaseSlot(QKeyEvent *e);
  void mousePressSlot(QMouseEvent *e);
  void mouseReleaseSlot(QMouseEvent *e);
  void mouseMoveSlot(QMouseEvent *e);
 signals:
  void ConfigUpdated();

 private:
  Camera &camera_;
};


#endif  // CAMERASPACER_H
