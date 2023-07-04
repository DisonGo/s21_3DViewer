#ifndef CAMERA_H
#define CAMERA_H
#include <QOpenGLFunctions>
#include <QVector3D>

#include "E/EObject.h"
#include "Shaders/Program.h"

class Camera : public EObject, protected QOpenGLFunctions {
 public:
  friend class CameraSpacer;
  explicit Camera();
  Camera(int width, int height);
  enum CameraMode { kFree = 0, kFocus = 1 };
  enum ViewMode { kPerspective = 0, kOrthographic = 1 };
  class ParallelBox {
   public:
    ParallelBox(float vertical, float horizontal)
        : top_(vertical),
          right_(horizontal),
          bottom_(vertical),
          left_(horizontal){};
    ParallelBox(float top = 1, float right = 1, float bottom = -1,
                float left = -1)
        : top_(top), right_(right), bottom_(bottom), left_(left){};
    float top_ = 1;
    float right_ = 1;
    float bottom_ = -1;
    float left_ = -1;
  };

  void Matrix(Program &program, const char *uniform);
  virtual EObjectType GetType() const override { return type_; };

 public:  // Setters / Getters
  void SetMode(CameraMode newMode);
  void SetViewMode(ViewMode newViewMode);
  void SetFocusPoint(const QVector3D &newFocusPoint);
  void SetPosition(const QVector3D &newPosition);
  void SetOrientation(const QVector3D &newOrientation);
  void SetZRange(const QVector2D &newZRange);
  void SetFOV(float newFOV);
  void SetVw(int newVw);
  void SetVh(int newVh);
  void SetMoveSpeed(float newMoveSpeed);
  void SetRotationSpeed(float newRotationSpeed);
  void SetBox(const ParallelBox &newBox);

  Camera::CameraMode GetMode() const;
  Camera::ViewMode GetViewMode() const;
  const QVector3D &GetFocusPoint() const;
  const QVector3D &GetPosition() const;
  const QVector3D &GetOrientation() const;
  const QVector2D &GetZRange() const;
  float GetFOV() const;
  int GetVw() const;
  int GetVh() const;
  float GetMoveSpeed() const;
  float GetRotationSpeed() const;
  const Camera::ParallelBox &GetBox() const;

 protected:
  EObjectType type_ = EObjectType::kCamera;

 private:  // Methods
  void ProcessFreeMode(QPoint ePos);
  void ProcessFocusMode(QPoint focusPoint);

 private:  // vars
  CameraMode mode_ = kFree;
  ViewMode view_mode_ = kPerspective;
  QVector3D focus_point_ = QVector3D(0, 0, 0);
  QVector3D position_ = QVector3D(0, 0, 0);
  QVector3D orientation_ = QVector3D(0, 0, 1);
  QVector2D z_range_ = QVector2D(0.001, 100);

  QVector3D up_ = QVector3D(0.0f, 1.0f, 0.0f);
  float FOV_ = 130;

  bool LMBPressed_ = false;
  int vw_ = 1;
  int vh_ = 1;
  QPoint m_center_pos_ = QPoint(0, 0);
  float move_speed_ = 0.1f;
  float rotation_speed_ = 0.1f;
  ParallelBox box_{};
};

#endif  // CAMERA_H
