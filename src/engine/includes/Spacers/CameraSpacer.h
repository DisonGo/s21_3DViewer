#ifndef CAMERASPACER_H
#define CAMERASPACER_H
#include <QKeyEvent>
#include <QObject>

#include "E/Camera.h"
namespace s21 {
class CameraSpacer : public QObject {
  Q_OBJECT
  using Vector3D = godison::vectors::Vector3D;
  using Vector2D = godison::vectors::Vector2D;

 public:
  CameraSpacer(Camera &camera_, QObject *parent = nullptr);
  void SetMode(Camera::CameraMode newMode);
  void SetViewMode(Camera::ViewMode newViewMode);
  void SetFocusPoint(const Vector3D &newFocusPoint);
  void SetPosition(const Vector3D &newPosition);
  void SetOrientation(const Vector3D &newOrientation);
  void SetZRange(const Vector2D &newZRange);
  void SetFOV(float newFOV);
  void SetVw(int newVw);
  void SetVh(int newVh);
  void SetMoveSpeed(float newMoveSpeed);
  void SetRotationSpeed(float newRotationSpeed);
  void SetBox(const Camera::ParallelBox &newBox);
  void SetLineWidth(double newLineWidth);

  Camera::CameraMode GetMode() const;
  Camera::ViewMode GetViewMode() const;
  const Vector3D &GetFocusPoint() const;
  const Vector3D &GetPosition() const;
  const Vector3D &GetOrientation() const;
  const Vector2D &GetZRange() const;
  float GetFOV() const;
  int GetVw() const;
  int GetVh() const;
  float GetMoveSpeed() const;
  float GetRotationSpeed() const;
  const Camera::ParallelBox &GetBox() const;
  double GetLineWidth();

 public slots:
  void keyPressSlot(QKeyEvent *e);
  void keyReleaseSlot(QKeyEvent *e);
  void mousePressSlot(QMouseEvent *e);
  void mouseReleaseSlot(QMouseEvent *e);
  void mouseMoveSlot(QMouseEvent *e);
  void wheelEventSlot(QWheelEvent *e);
 signals:
  void ConfigUpdated();

 private:
  Camera &camera_;
};
}  // namespace s21

#endif  // CAMERASPACER_H
