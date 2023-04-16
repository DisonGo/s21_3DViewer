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
Camera::Camera(int width, int height, QObject *parent) : QObject(parent) {
  setVw(width);
  setVh(height);
  initializeOpenGLFunctions();
}

void Camera::Matrix(Shader &shader, const char *uniform)
{
  QMatrix4x4 view, projection, model;
  moveSpeed = abs(zRange.y() - zRange.x()) / 1000;
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
    projection.ortho(boxLeft, boxRight, boxBottom, boxTop, zRange.x() , zRange.y() ) ;
  if (viewMode == Perspective)
    projection.perspective(FOV, (float)vw / vh, zRange.x() , zRange.y() );
  glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, (projection * view).constData());
}

void Camera::keyPressSlot(QKeyEvent *e)
{
  int key = e->key();

  if (key == Qt::Key_Shift)
    setMoveSpeed(moveSpeed);
  if (mode == Free) {
    QVector3D Buf = Position;
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
    if (Buf != Position)
      emit ConfigUpdated(assembleConfig());
  }

//  if (mode == Focus) {
//    if (!( key == Qt::Key_W
//        || key == Qt::Key_A
//        || key == Qt::Key_S
//        || key == Qt::Key_D)) return;        // Rotate left around the center of rotation
//    QMatrix4x4 RotateMat;
//    RotateMat.setToIdentity();
//    QVector3D C = QVector3D::crossProduct(FocusPoint, Position);

//    // Calculate the vector representing the x-axis of the plane
//    QVector3D AxisX = QVector3D::crossProduct(Position, C).normalized();

//    // Calculate the vector representing the y-axis of the plane
//    QVector3D AxisY = QVector3D::crossProduct(C, AxisX);
////    AxisX.normalize();
////    AxisY.normalize();
////    if (FocusPoint != QVector3D(0,0,0)) {
//////      AxisY = QVector3D::normal(Position, FocusPoint);
//////      AxisX =
//      qDebug() << AxisX;
//      qDebug() << AxisY;
////    }
////    RotateMat.translate(Position);
////    RotateMat.translate(FocusPoint);
//    if (key == Qt::Key_W) {
//      RotateMat.rotate(rotationSpeed, AxisX);
//    }
//    if (key == Qt::Key_S) {
//      RotateMat.rotate(-rotationSpeed, AxisX);
//    }
//    if (key == Qt::Key_A) {
//      RotateMat.rotate(rotationSpeed, AxisY);
//    }
//    if (key == Qt::Key_D) {
//      RotateMat.rotate(-rotationSpeed, AxisY);
//    }
//    Position = RotateMat.map(Position);

//  }
}
void Camera::keyReleaseSlot(QKeyEvent *e) {

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
  emit ConfigUpdated(assembleConfig());
}

void Camera::SetConfig(CameraConfig config)
{
  mode = config.Mode;
  viewMode = config.viewMode;
  FocusPoint = config.FocusPoint;
  Position = config.Position;
  Orientation = config.Orientation;
  zRange = config.zRange;
  FOV = config.FOV;
  boxLeft = config.boxLeft;
  boxRight = config.boxRight;
  boxBottom = config.boxBottom;
  boxTop = config.boxTop;
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


void Camera::setZRange(const QVector2D &newZRange)
{
  zRange = newZRange;
  emit ConfigUpdated(assembleConfig());
}

void Camera::setFOV(float newFOV)
{
  FOV = newFOV;
  emit ConfigUpdated(assembleConfig());
}

void Camera::setVw(int newVw)
{
  vw = newVw;
}

void Camera::setVh(int newVh)
{
  vh = newVh;
}

void Camera::setMoveSpeed(float newMoveSpeed)
{
  moveSpeed = newMoveSpeed;
}

void Camera::setRotationSpeed(float newRotationSpeed)
{
  rotationSpeed = newRotationSpeed;
}

const Camera::CameraConfig& Camera::assembleConfig()
{
  config.Mode = mode;
  config.viewMode = viewMode;
  config.FocusPoint = FocusPoint;
  config.Position = Position;
  config.Orientation = Orientation;
  config.zRange = zRange;
  config.FOV = FOV;
  config.boxTop = boxTop;
  config.boxBottom = boxBottom;
  config.boxRight = boxRight;
  config.boxLeft = boxLeft;
  return config;
}

void Camera::setOrientation(const QVector3D &newOrientation)
{
  Orientation = newOrientation;
  emit ConfigUpdated(assembleConfig());
}

void Camera::setViewMode(ViewMode newViewMode)
{
  viewMode = newViewMode;
  emit ConfigUpdated(assembleConfig());
}

void Camera::setFocusPoint(const QVector3D &newFocusPoint)
{
  FocusPoint = newFocusPoint;
  emit ConfigUpdated(assembleConfig());
}

void Camera::setPosition(const QVector3D &newPosition)
{
  Position = newPosition;
  emit ConfigUpdated(assembleConfig());
}

void Camera::setMode(CameraMode newMode)
{
  mode = newMode;
  emit ConfigUpdated(assembleConfig());
}

