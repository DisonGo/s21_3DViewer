#ifndef CAMERA_H
#define CAMERA_H
#include <godison/Matrices.h>
#include <godison/Point.h>

#include <QOpenGLFunctions>
#include "GL/UBO.h"
#include "E/EObject.h"
#include "Shaders/Program.h"
namespace s21 {
class Camera : public EObject, protected QOpenGLFunctions {
 public:
  using Vector2D = godison::vectors::Vector2D;
  using Vector3D = godison::vectors::Vector3D;
  using GPoint = godison::GPoint;
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

  void Matrix(Program &program);
  virtual EObjectType GetType() const override { return type_; };

 public:  // Setters / Getters
  void SetMode(CameraMode newMode);
  void SetViewMode(ViewMode newViewMode);
  void SetFocusPoint(const Vector3D &newFocusPoint);
  void SetPosition(const Vector3D &newPosition);
  void SetOrientation(const Vector3D &newOrientation);
  void SetZRange(const Vector2D &newZRange);
  void SetFOV(float newFOV);
  void SetVw(int newVw);
  void SetVh(int newVh);
  void SetMoveSpeed(float newMoveSpeed);
  void SetRotationSpeed(float newRotationSpeed);
  void SetBox(const ParallelBox &newBox);
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
  double GetLineWidth() const;

  double GetZoomFactor() const;
  void SetZoomFactor(double newZoomFactor);
  void SetDefaultUBOData(UBO& ubo);

 protected:
  EObjectType type_ = EObjectType::kCamera;

 private:  // Methods
  void ProcessFreeMode(GPoint ePos);
  void ProcessFocusMode(GPoint ePos);
  void CalcFocusPosition();

 private:  // vars
  godison::matrices::Matrix4x4 view_, projection_;
  CameraMode mode_ = kFocus;
  ViewMode view_mode_ = kPerspective;
  Vector3D focus_point_ = Vector3D(0, 1, 0);
  Vector3D position_ = Vector3D(1, 1, 1);
  Vector3D orientation_ = Vector3D(0, 1);
  Vector2D z_range_ = Vector2D(0.001, 100);
  Vector3D focus_rotation_ = Vector3D(0, 0, 0);
  Vector3D up_ = Vector3D(0.0f, 1.0f, 0.0f);

  float FOV_ = 130;
  double lineWidth_ = 1;
  double sensitivity_ = 20;
  double zoom_factor = 1;
  bool LMBPressed_ = false;
  int vw_ = 1;
  int vh_ = 1;
  GPoint m_center_pos_ = GPoint(0, 0);
  float move_speed_ = 0.1f;
  float rotation_speed_ = 1.f;
  ParallelBox box_{};
};
}  // namespace s21

#endif  // CAMERA_H
