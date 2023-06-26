#include "camera.h"

#include <QMatrix4x4>

#include "QtMath"
Camera::Camera() : config_(*this) {
  SetVh(0);
  SetVw(0);
  SetPosition(QVector3D(0, 0, 0));
  initializeOpenGLFunctions();
}
Camera::Camera(int width, int height)
    : config_(*this) {
  SetVw(width);
  SetVh(height);
  initializeOpenGLFunctions();
}

void Camera::Matrix(Shader &shader, const char *uniform) {
  QMatrix4x4 view, projection, model;
  moveSpeed = abs(zRange.y() - zRange.x()) / 1000;
  rotationSpeed = 10;
  model.setToIdentity();
  view.setToIdentity();
  projection.setToIdentity();
  model.translate(Position);
  QVector3D lookAtVec(0, 0, 0);
  if (mode == Free) lookAtVec = Orientation + Position;
  if (mode == Focus) lookAtVec = FocusPoint;
  view.lookAt(Position, lookAtVec, Up);
  if (viewMode == Orthographic)
    projection.ortho(box.left, box.right, box.bottom, box.top, zRange.x(),
                     zRange.y());
  if (viewMode == Perspective)
    projection.perspective(FOV, (float)vw / vh, zRange.x(), zRange.y());
  glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE,
                     (projection * view).constData());
}

void Camera::processFreeMode(QPoint ePos) {
  if (!LMBPressed) return;

  // Stores the coordinates of the cursor
  double mouseX = ePos.rx();
  double mouseY = ePos.ry();

  // Normalizes and shifts the coordinates of the cursor such that they begin in
  // the middle of the screen and then "transforms" them into degrees

  float rotX = rotationSpeed * (float)(mouseY - (vh / 2)) / vh;
  float rotY = rotationSpeed * (float)(mouseX - (vw / 2)) / vw;

  // Calculates upcoming vertical change in the Orientation

  QMatrix4x4 rotationMatrix;
  rotationMatrix.setToIdentity();
  rotationMatrix.rotate(-rotX, QVector3D::normal(Orientation, Up));
  QVector3D newOrientation = rotationMatrix.map(Orientation);

  // Decides whether or not the next vertical Orientation is legal or not

  float dotProd = QVector3D::dotProduct(newOrientation, Up);
  float angle =
      qAcos(dotProd / (newOrientation.length() * Up.length())) * 180 / M_PI;
  if (abs(angle - 90.0f) <= 85.0f) Orientation = newOrientation;
  rotationMatrix.setToIdentity();
  rotationMatrix.rotate(-rotY, Up);

  // Rotates the Orientation left and right

  Orientation = rotationMatrix.map(Orientation);
}

void Camera::SetZRange(const QVector2D &newZRange) { zRange = newZRange; }

void Camera::SetFOV(float newFOV) { FOV = newFOV; }

void Camera::SetVw(int newVw) { vw = newVw; }

void Camera::SetVh(int newVh) { vh = newVh; }

void Camera::SetMoveSpeed(float newMoveSpeed) { moveSpeed = newMoveSpeed; }

void Camera::SetRotationSpeed(float newRotationSpeed) {
  rotationSpeed = newRotationSpeed;
}

void Camera::SetOrientation(const QVector3D &newOrientation) {
  Orientation = newOrientation;
}

void Camera::SetViewMode(ViewMode newViewMode) { viewMode = newViewMode; }

void Camera::SetFocusPoint(const QVector3D &newFocusPoint) {
  FocusPoint = newFocusPoint;
}

void Camera::SetPosition(const QVector3D &newPosition) {
  Position = newPosition;
}

void Camera::SetMode(CameraMode newMode) { mode = newMode; }
