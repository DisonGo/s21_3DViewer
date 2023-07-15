#include "E/Camera.h"

#include <QMatrix4x4>

#include "E/Point.h"
#include "QtMath"
namespace s21 {
Camera::Camera() {
  SetVh(0);
  SetVw(0);
  initializeOpenGLFunctions();
}
Camera::Camera(int width, int height) {
  SetVw(width);
  SetVh(height);
  initializeOpenGLFunctions();
}

void Camera::Matrix(Program &program, const char *uniform) {
  QMatrix4x4 view, projection, rotation;
  move_speed_ = abs(z_range_.Y() - z_range_.X()) / 1000;
  rotation_speed_ = 10;

  if (mode_ == kFocus) CalcFocusPosition();
  if (mode_ == kFree) view.lookAt(position_, orientation_ + position_, up_);
  if (mode_ == kFocus) view.lookAt(position_, focus_point_, up_);

  if (view_mode_ == kOrthographic)
    projection.ortho(box_.left_, box_.right_, box_.bottom_, box_.top_,
                     z_range_.X(), z_range_.Y());
  if (view_mode_ == kPerspective)
    projection.perspective(FOV_, (float)vw_ / vh_, z_range_.X(), z_range_.Y());
  glUniformMatrix4fv(program.GetUniform(uniform), 1, GL_FALSE,
                     (projection * view).constData());
  glUniformMatrix4fv(program.GetUniform("m_CameraView"), 1, GL_FALSE,
                     (view).constData());
  glUniformMatrix4fv(program.GetUniform("m_CameraProjection"), 1, GL_FALSE,
                     (projection).constData());

  glUniform3f(program.GetUniform("u_CameraPos"), position_.X(), position_.Y(),
              position_.Z());
  glUniform2f(program.GetUniform("u_resolution"), vw_, vh_);
  glUniform1f(program.GetUniform("u_dashSize"), 1);
  glUniform1f(program.GetUniform("u_gapSize"), 1);
  glUniform1f(program.GetUniform("u_lineWidth"), lineWidth_);
}

void Camera::ProcessFreeMode(godison::Point ePos) {
  if (!LMBPressed_) return;
  Vector2D dif(ePos - m_center_pos_);
  dif.Normalize();
  float rotX = dif.Y() * rotation_speed_ / 2;
  float rotY = dif.X() * rotation_speed_ / 2;
  m_center_pos_ = ePos;
  // Calculates upcoming vertical change in the Orientation

  QMatrix4x4 rotationMatrix;
  rotationMatrix.rotate(-rotX, Vector3D::Normal(orientation_, up_));
  Vector3D newOrientation = rotationMatrix.map(orientation_);

  // Decides whether or not the next vertical Orientation is legal or not

  float dotProd = Vector3D::DotProduct(newOrientation, up_);
  float angle =
      qAcos(dotProd / (newOrientation.length() * up_.length())) * 180 / M_PI;
  if (abs(angle - 90.0f) <= 85.0f) orientation_ = newOrientation;
  rotationMatrix.setToIdentity();
  rotationMatrix.rotate(-rotY, up_);

  // Rotates the Orientation left and right

  orientation_ = rotationMatrix.map(orientation_);
}

void Camera::ProcessFocusMode(godison::Point ePos) {
  Vector2D dif(ePos - m_center_pos_);
  dif.Normalize();

  sensitivity_ = 20 * M_PI / (std::min(vw_, vh_));
  float azimuth = dif.X() * sensitivity_;
  float elevation = dif.Y() * sensitivity_;

  focus_rotation_.SetX(azimuth);
  focus_rotation_.SetZ(elevation);
  m_center_pos_ = ePos;
}

void Camera::CalcFocusPosition() {
  //  static const Vector3D yAxis(0.0f, 1.0f, 0.0f);
  constexpr double MIN_DIST = 0.1;
  float distance = (position_ - focus_point_).Length();
  if (distance * zoom_factor > MIN_DIST) distance *= zoom_factor;
  zoom_factor = 1;
  orientation_ = (position_ - focus_point_).Normalized();
  if (orientation_.Y() > 0.95) orientation_.SetY(0.95);
  if (orientation_.Y() < -0.95) orientation_.SetY(-0.95);
  //  Recalculating basic axis;
  //  Vector3D cameraSide = Vector3D::CrossProduct(yAxis,
  //  orientation_).normalized(); up_ = Vector3D::CrossProduct(orientation_,
  //  cameraSide);

  float pitchAngle = asin(orientation_.Y());
  float yawAngle = atan2(orientation_.X(), orientation_.Z());

  pitchAngle -= focus_rotation_.Z();  // elevation
  yawAngle -= focus_rotation_.X();    // azimuth
  focus_rotation_ = Vector3D();
  yawAngle = fmod(yawAngle, 2 * M_PI);

  Vector3D newDir(cos(pitchAngle) * sin(yawAngle), sin(pitchAngle),
                  cos(pitchAngle) * cos(yawAngle));
  position_ = focus_point_ + distance * newDir;
}

}  // namespace s21
