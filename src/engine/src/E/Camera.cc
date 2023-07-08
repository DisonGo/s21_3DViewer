#include "E/Camera.h"

#include <QMatrix4x4>

#include "QtMath"
namespace s21 {
Camera::Camera() {
  SetVh(0);
  SetVw(0);
  SetPosition(QVector3D(0, 1, 0));
  initializeOpenGLFunctions();
}
Camera::Camera(int width, int height) {
  SetVw(width);
  SetVh(height);
  initializeOpenGLFunctions();
}

void Camera::Matrix(Program &program, const char *uniform) {
  QMatrix4x4 view, projection, model;
  move_speed_ = abs(z_range_.y() - z_range_.x()) / 1000;
  rotation_speed_ = 10;
  model.translate(position_);
  QVector3D lookAtVec(0, 0, 0);

  if (mode_ == kFree) lookAtVec = orientation_ + position_;
  if (mode_ == kFocus) lookAtVec = focus_point_;
  view.lookAt(position_, lookAtVec, up_);

  if (view_mode_ == kOrthographic)
    projection.ortho(box_.left_, box_.right_, box_.bottom_, box_.top_,
                     z_range_.x(), z_range_.y());
  if (view_mode_ == kPerspective)
    projection.perspective(FOV_, (float)vw_ / vh_, z_range_.x(), z_range_.y());
  glUniformMatrix4fv(program.GetUniform(uniform), 1, GL_FALSE,
                     (projection * view).constData());
  glUniformMatrix4fv(program.GetUniform("m_CameraView"), 1, GL_FALSE,
                     (view).constData());
  glUniformMatrix4fv(program.GetUniform("m_CameraProjection"), 1, GL_FALSE,
                     (projection).constData());

  glUniform3f(program.GetUniform("u_CameraPos"), position_.x(), position_.y(),
              position_.z());
  glUniform2f(program.GetUniform("u_resolution"), vw_, vh_);
  glUniform1f(program.GetUniform("u_dashSize"), 1);
  glUniform1f(program.GetUniform("u_gapSize"), 1);
  glUniform1f(program.GetUniform("u_lineWidth"), lineWidth_);
}

void Camera::ProcessFreeMode(QPoint ePos) {
  if (!LMBPressed_) return;

  // Stores the coordinates of the cursor
  double mouseX = ePos.rx();
  double mouseY = ePos.ry();

  // Normalizes and shifts the coordinates of the cursor such that they begin in
  // the middle of the screen and then "transforms" them into degrees

  float rotX = rotation_speed_ * (float)(mouseY - (vh_ / 2)) / vh_;
  float rotY = rotation_speed_ * (float)(mouseX - (vw_ / 2)) / vw_;

  // Calculates upcoming vertical change in the Orientation

  QMatrix4x4 rotationMatrix;
  rotationMatrix.rotate(-rotX, QVector3D::normal(orientation_, up_));
  QVector3D newOrientation = rotationMatrix.map(orientation_);

  // Decides whether or not the next vertical Orientation is legal or not

  float dotProd = QVector3D::dotProduct(newOrientation, up_);
  float angle =
      qAcos(dotProd / (newOrientation.length() * up_.length())) * 180 / M_PI;
  if (abs(angle - 90.0f) <= 85.0f) orientation_ = newOrientation;
  rotationMatrix.setToIdentity();
  rotationMatrix.rotate(-rotY, up_);

  // Rotates the Orientation left and right

  orientation_ = rotationMatrix.map(orientation_);
}

void Camera::SetZRange(const QVector2D &newZRange) { z_range_ = newZRange; }

void Camera::SetFOV(float newFOV) { FOV_ = newFOV; }

void Camera::SetVw(int newVw) { vw_ = newVw; }

void Camera::SetVh(int newVh) { vh_ = newVh; }

void Camera::SetMoveSpeed(float newMoveSpeed) { move_speed_ = newMoveSpeed; }

void Camera::SetRotationSpeed(float newRotationSpeed) {
  rotation_speed_ = newRotationSpeed;
}

void Camera::SetOrientation(const QVector3D &newOrientation) {
  orientation_ = newOrientation;
}

void Camera::SetViewMode(ViewMode newViewMode) { view_mode_ = newViewMode; }

void Camera::SetFocusPoint(const QVector3D &newFocusPoint) {
  focus_point_ = newFocusPoint;
}

void Camera::SetPosition(const QVector3D &newPosition) {
  position_ = newPosition;
}

void Camera::SetMode(CameraMode newMode) { mode_ = newMode; }
void Camera::SetBox(const ParallelBox &newBox) { box_ = newBox; }
void Camera::SetLineWidth(double newLineWidth) { lineWidth_ = newLineWidth; }

Camera::CameraMode Camera::GetMode() const { return mode_; };
Camera::ViewMode Camera::GetViewMode() const { return view_mode_; };
const QVector3D &Camera::GetFocusPoint() const { return focus_point_; };
const QVector3D &Camera::GetPosition() const { return position_; };
const QVector3D &Camera::GetOrientation() const { return orientation_; };
const QVector2D &Camera::GetZRange() const { return z_range_; };
float Camera::GetFOV() const { return FOV_; };
int Camera::GetVw() const { return vw_; };
int Camera::GetVh() const { return vh_; };
float Camera::GetMoveSpeed() const { return move_speed_; };
float Camera::GetRotationSpeed() const { return rotation_speed_; };
const Camera::ParallelBox &Camera::GetBox() const { return box_; }
double Camera::GetLineWidth() const { return lineWidth_; };
}  // namespace s21
