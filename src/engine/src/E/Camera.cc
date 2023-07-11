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
  move_speed_ = abs(z_range_.y() - z_range_.x()) / 1000;
  rotation_speed_ = 10;

  if (mode_ == kFocus) CalcFocusPosition();
  if (mode_ == kFree) view.lookAt(position_, orientation_ + position_, up_);
  if (mode_ == kFocus) view.lookAt(position_, focus_point_, up_);

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

  QVector2D dif(ePos - m_center_pos_);
  dif.normalize();
  float rotX = dif.y() * rotation_speed_ / 2;
  float rotY = dif.x() * rotation_speed_ / 2;
  m_center_pos_ = ePos;
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

void Camera::ProcessFocusMode(QPoint ePos) {
  QVector2D dif(ePos - m_center_pos_);
  dif.normalize();

  sensitivity_ = 20 * M_PI / (std::min(vw_, vh_));
  float azimuth = dif.x() * sensitivity_;
  float elevation = dif.y() * sensitivity_;

  focus_rotation_.setX(azimuth);
  focus_rotation_.setZ(elevation);
  m_center_pos_ = ePos;
}

void Camera::CalcFocusPosition() {
  //  static const QVector3D yAxis(0.0f, 1.0f, 0.0f);
  constexpr double MIN_DIST = 0.1;
  float distance = (position_ - focus_point_).length();
  if (distance * zoom_factor > MIN_DIST) distance *= zoom_factor;
  zoom_factor = 1;
  orientation_ = (position_ - focus_point_).normalized();
  if (orientation_.y() > 0.95) orientation_.setY(0.95);
  if (orientation_.y() < -0.95) orientation_.setY(-0.95);
  //  Recalculating basic axis;
  //  QVector3D cameraSide = QVector3D::crossProduct(yAxis,
  //  orientation_).normalized(); up_ = QVector3D::crossProduct(orientation_,
  //  cameraSide);

  float pitchAngle = asin(orientation_.y());
  float yawAngle = atan2(orientation_.x(), orientation_.z());

  pitchAngle -= focus_rotation_.z();  // elevation
  yawAngle -= focus_rotation_.x();    // azimuth
  focus_rotation_ = QVector3D();
  yawAngle = fmod(yawAngle, 2 * M_PI);

  QVector3D newDir(cos(pitchAngle) * sin(yawAngle), sin(pitchAngle),
                   cos(pitchAngle) * cos(yawAngle));
  position_ = focus_point_ + distance * newDir;
}

}  // namespace s21
