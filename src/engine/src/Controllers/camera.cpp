#include "camera.h"
#include "QtMath"
#include <QMatrix4x4>
Camera::Camera(QObject *parent) : QObject(parent)
{
  setVh(0);
  setVw(0);
  setPosition(QVector3D(0,0,0));
  initializeOpenGLFunctions();
}
Camera::Camera(int width, int height, QVector3D position, QObject *parent) : QObject(parent) {
  setVw(width);
  setVh(height);
  setPosition(position);
  initializeOpenGLFunctions();
}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader &shader, const char *uniform)
{

  QMatrix4x4 view, projection, model;
  baseSpeed = abs(farPlane - nearPlane) / 1000;
  moveSpeed = baseSpeed;
  rotationSpeed = 10;
  model.setToIdentity();
  view.setToIdentity();
  projection.setToIdentity();
  model.translate(Position);
  QVector3D lookAtVec(0,0,0);
  if (mode == Free)
    lookAtVec = Orientation + Position;
  if (mode == Focus)
    lookAtVec = FocusPoint;
  view.lookAt(Position, lookAtVec, Up);
  if (viewMode == Orthographic)
    projection.ortho(-100, 100, -100, 100, nearPlane, farPlane) ;
  if (viewMode == Perspective)
    projection.perspective(FOVdeg, (float)vw / vh, nearPlane, farPlane);
  glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, (projection * view).constData());
//  glUniformMatrix4fv(glGetUniformLocation(shader.ID, "camModel"), 1, GL_FALSE, model.constData());
//  glUniformMatrix4fv(glGetUniformLocation(shader.ID, "camView"), 1, GL_FALSE, view.constData());
//  glUniformMatrix4fv(glGetUniformLocation(shader.ID, "camProjection"), 1, GL_FALSE, projection.constData());

}

void Camera::keyPressSlot(QKeyEvent *e)
{
  int key = e->key();

  if (key == Qt::Key_Shift)
    setSpeed(baseSpeed * multiSpeed);
  if (mode == Free) {
    if (key == Qt::Key_W)
      Position += moveSpeed * Orientation;
    if (key == Qt::Key_A)
      Position += moveSpeed * -QVector3D::normal(Orientation, Up) * 0.1;
    if (key == Qt::Key_S)
      Position += moveSpeed * -Orientation;
    if (key == Qt::Key_D)
      Position += moveSpeed * QVector3D::normal(Orientation, Up) * 0.1;
    if (key == Qt::Key_Space)
      Position += moveSpeed * Up;
    if (key == Qt::Key_Control)
      Position += moveSpeed * -Up;
  }

  if (mode == Focus) {
    if (!( key == Qt::Key_W
        || key == Qt::Key_A
        || key == Qt::Key_S
        || key == Qt::Key_D)) return;        // Rotate left around the center of rotation
    QMatrix4x4 RotateMat;
    RotateMat.setToIdentity();
    QVector3D C = QVector3D::crossProduct(FocusPoint, Position);

    // Calculate the vector representing the x-axis of the plane
    QVector3D AxisX = QVector3D::crossProduct(Position, C).normalized();

    // Calculate the vector representing the y-axis of the plane
    QVector3D AxisY = QVector3D::crossProduct(C, AxisX);
//    AxisX.normalize();
//    AxisY.normalize();
//    if (FocusPoint != QVector3D(0,0,0)) {
////      AxisY = QVector3D::normal(Position, FocusPoint);
////      AxisX =
      qDebug() << AxisX;
      qDebug() << AxisY;
//    }
//    RotateMat.translate(Position);
//    RotateMat.translate(FocusPoint);
    if (key == Qt::Key_W) {
      RotateMat.rotate(rotationSpeed, AxisX);
    }
    if (key == Qt::Key_S) {
      RotateMat.rotate(-rotationSpeed, AxisX);
    }
    if (key == Qt::Key_A) {
      RotateMat.rotate(rotationSpeed, AxisY);
    }
    if (key == Qt::Key_D) {
      RotateMat.rotate(-rotationSpeed, AxisY);
    }
    Position = RotateMat.map(Position);

  }
}
void Camera::keyReleaseSlot(QKeyEvent *e) {
  int key = e->key();
  if (key == Qt::Key_Shift)
    setSpeed(baseSpeed);
}
void Camera::mousePressSlot(QMouseEvent *e)
{
  LMBPressed = true;
  mCenterPos = e->pos();
}

void Camera::mouseReleaseSlot(QMouseEvent *e)
{
  LMBPressed = false;
}

void Camera::mouseMoveSlot(QMouseEvent *e)
{
  processFreeMode(e->pos());
}

void Camera::wheelSlot(QWheelEvent *e)
{
//  float increment_sign = e->angleDelta().ry() > 0 ? 1 : -1;
//  float distance = FocusPoint.distanceToPoint(Position) + moveSpeed * -increment_sign;
//  QVector3D norm_displacement = (Position - FocusPoint).normalized();
//  QVector3D new_Position = FocusPoint + norm_displacement * distance;
//  if (new_Position == QVector3D(0,0,0)) return;
//  Position = new_Position;
//  CameraData new_data = {
//    QPoint(0,0),
//    QPoint(0,0),
//    0,
//    0,
//    0,
//    moveSpeed,
//    FocusPoint,
//    Position
//  };
//  emit dataUpdated(new_data);
}

const QVector3D &Camera::getPosition() const
{
  return Position;
}

void Camera::setPosition(const QVector3D &newPosition)
{
  Position = newPosition;
}

int Camera::getVw() const
{
  return vw;
}

void Camera::setVw(int newVw)
{
  vw = newVw;
}

int Camera::getVh() const
{
  return vh;
}

void Camera::setVh(int newVh)
{
  vh = newVh;
}

void Camera::setSpeed(float newSpeed)
{
  moveSpeed = newSpeed;
}


void Camera::processFreeMode(QPoint ePos)
{
    if (!LMBPressed) return;

    // Stores the coordinates of the cursor
    double mouseX = ePos.rx();
    double mouseY = ePos.ry();

    // Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
    // and then "transforms" them into degrees

    float rotX = rotationSpeed * (float)(mouseY - (vh / 2)) / vh;
    float rotY = rotationSpeed * (float)(mouseX - (vw / 2)) / vw;

    // Calculates upcoming vertical change in the Orientation

    QMatrix4x4 rotationMatrix;
    rotationMatrix.setToIdentity();
    rotationMatrix.rotate(-rotX, QVector3D::normal(Orientation, Up));
    QVector3D newOrientation = rotationMatrix.map(Orientation);

    // Decides whether or not the next vertical Orientation is legal or not

    float dotProd = QVector3D::dotProduct(newOrientation, Up);
    float angle = qAcos(dotProd / (newOrientation.length() * Up.length())) * 180 / M_PI;
    if (abs(angle - 90.0f) <= 85.0f)
      Orientation = newOrientation;
    rotationMatrix.setToIdentity();
    rotationMatrix.rotate(-rotY, Up);

    // Rotates the Orientation left and right

    Orientation = rotationMatrix.map(Orientation);
}

const QVector3D &Camera::getOrientation() const
{
  return Orientation;
}

void Camera::setOrientation(const QVector3D &newOrientation)
{
  Orientation = newOrientation;
}

Camera::ViewMode Camera::getViewMode() const
{
  return viewMode;
}

void Camera::setViewMode(ViewMode newViewMode)
{
  viewMode = newViewMode;
}

void Camera::setFocusPoint(const QVector3D &newFocusPoint)
{
  FocusPoint = newFocusPoint;
}

Camera::CameraMode Camera::getMode() const
{
  return mode;
}

void Camera::setMode(CameraMode newMode)
{
  mode = newMode;
}

