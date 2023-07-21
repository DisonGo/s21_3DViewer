#include "E/Camera.h"
using godison::vectors::Vector2D;
using godison::vectors::Vector3D;
using godison::vectors::Vector4D;
namespace s21 {
// Setters

void Camera::SetZRange(const Vector2D &newZRange) { z_range_ = newZRange; }
void Camera::SetFOV(float newFOV) { FOV_ = newFOV; }
void Camera::SetVw(int newVw) { vw_ = newVw; }
void Camera::SetVh(int newVh) { vh_ = newVh; }
void Camera::SetMoveSpeed(float newMoveSpeed) { move_speed_ = newMoveSpeed; }
void Camera::SetRotationSpeed(float newRotationSpeed) {
  rotation_speed_ = newRotationSpeed;
}
void Camera::SetOrientation(const Vector3D &newOrientation) {
  orientation_ = newOrientation;
}
void Camera::SetViewMode(ViewMode newViewMode) { view_mode_ = newViewMode; }
void Camera::SetFocusPoint(const Vector3D &newFocusPoint) {
  focus_point_ = newFocusPoint;
}
void Camera::SetPosition(const Vector3D &newPosition) {
  position_ = newPosition;
}
void Camera::SetMode(CameraMode newMode) { mode_ = newMode; }
void Camera::SetBox(const ParallelBox &newBox) { box_ = newBox; }
void Camera::SetLineWidth(double newLineWidth) { lineWidth_ = newLineWidth; }
void Camera::SetZoomFactor(double newZoomFactor) {
  zoom_factor = newZoomFactor;
}

void Camera::SetDefaultUBOData(UBO *ubo)
{
  // Mapping UBO data
  unsigned offset = 0;
  static const auto s_vec2 = sizeof(Vector2D().Data()); // 8
  static const auto s_vec4 = sizeof(Vector4D().Data()); // 16
  static const auto s_mat4 = sizeof(godison::matrices::Matrix4x4().Data()); // 64
  Vector2D resolution(vw_, vh_);
  // RESOLUTION
  ubo->BufferSubData(offset, s_vec2, &resolution.Data()[0]);
  // POSITION
//  ubo.BufferSubData(offset += s_vec2 * 2, s_vec4, position_.ToVector<4>(1).Data().data());
//  // PROJECTION
//  ubo.BufferSubData(offset += s_vec4, s_mat4, projection_.Data().data());
//  // VIEW
//  ubo.BufferSubData(offset += s_mat4, s_mat4, view_.Data().data());
//  // PROJECTION X VIEW
//  ubo.BufferSubData(offset += s_mat4, s_mat4, (projection_ * view_).Data().data());
  // 64 * 3 + 16 * 2 = 224 bytes
}

void Camera::PrintDefaultUBOData(UBO &ubo)
{

}
// Getters

Camera::CameraMode Camera::GetMode() const { return mode_; };
Camera::ViewMode Camera::GetViewMode() const { return view_mode_; };
const Vector3D &Camera::GetFocusPoint() const { return focus_point_; };
const Vector3D &Camera::GetPosition() const { return position_; };
const Vector3D &Camera::GetOrientation() const { return orientation_; };
const Vector2D &Camera::GetZRange() const { return z_range_; };
float Camera::GetFOV() const { return FOV_; };
int Camera::GetVw() const { return vw_; };
int Camera::GetVh() const { return vh_; };
float Camera::GetMoveSpeed() const { return move_speed_; };
float Camera::GetRotationSpeed() const { return rotation_speed_; };
const Camera::ParallelBox &Camera::GetBox() const { return box_; }
double Camera::GetLineWidth() const { return lineWidth_; };
double Camera::GetZoomFactor() const { return zoom_factor; }
}  // namespace s21
