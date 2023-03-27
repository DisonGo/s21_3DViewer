#include "camera.h"
#include "QtMath"
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
  // Initializes matrices since otherwise they will be the null matrix
    QMatrix4x4 view, projection;
    baseSpeed = abs(farPlane - nearPlane) / 1000;
    speed = baseSpeed;
    view.setToIdentity();
    projection.setToIdentity();
    // Makes camera look in the right direction from the right position
    QVector3D lookAtVec(0,0,0);
    if (mode == Free)
      lookAtVec = Orientation + Position;
    if (mode == Focus)
      lookAtVec = FocusPoint;
    view.lookAt(Position, lookAtVec, Up);
    // Adds perspective to the scene
    projection.perspective(FOVdeg, (float)vw / vh, nearPlane, farPlane);
//    qDebug() << "View mat:\n" << view << "Projection mat:\n" << projection;
    // Exports the camera matrix to the Vertex Shader
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, (projection * view).constData());
}

void Camera::keyPressSlot(QKeyEvent *e)
{
  int key = e->key();

  if (key == Qt::Key_Shift)
    setSpeed(baseSpeed * multiSpeed);

  if (mode == Free) {
    if (key == Qt::Key_W)
      Position += speed * Orientation;
    if (key == Qt::Key_A)
      Position += speed * -QVector3D::normal(Orientation, Up) * 0.1;
    if (key == Qt::Key_S)
      Position += speed * -Orientation;
    if (key == Qt::Key_D)
      Position += speed * QVector3D::normal(Orientation, Up) * 0.1;
    if (key == Qt::Key_Space)
      Position += speed * Up;
    if (key == Qt::Key_Control)
      Position += speed * -Up;
  }

  if (mode == Focus) {
    if (!( key == Qt::Key_W
        || key == Qt::Key_A
        || key == Qt::Key_S
        || key == Qt::Key_D)) return;
    QMatrix4x4 RotateMat;
    RotateMat.setToIdentity();
    QVector3D AxisX(1,0,0);
    QVector3D AxisY(0,1,0);
    if (FocusPoint != QVector3D(0,0,0)) {
      AxisY = QVector3D::crossProduct(Position, FocusPoint);
      AxisX = QVector3D::crossProduct(Position, AxisX);
    }
    float angle = speed;
    if (key == Qt::Key_W) {
      RotateMat.rotate(-angle, AxisX);
    }
    if (key == Qt::Key_S) {
      RotateMat.rotate(angle, AxisX);
    }
    if (key == Qt::Key_A) {
      RotateMat.rotate(-angle, AxisY);
    }
    if (key == Qt::Key_D) {
      RotateMat.rotate(angle, AxisY);
    }
    Position = RotateMat.map(Position);
  }
  CameraData new_data = {
    mCenterPos,
    QPoint(0,0),
    0,
    0,
    0,
    speed,
    Orientation,
    Position
  };
  emit dataUpdated(new_data);
}
void Camera::keyReleaseSlot(QKeyEvent *e) {
  int key = e->key();
  if (key == Qt::Key_Shift)
    setSpeed(baseSpeed);
  CameraData new_data = {
    mCenterPos,
    QPoint(0,0),
    0,
    0,
    0,
    speed,
    Orientation,
    Position
  };
  emit dataUpdated(new_data);
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

}

void Camera::wheelSlot(QWheelEvent *e)
{
  float increment = -e->angleDelta().ry()/15.0f/8/10;
  float distance = FocusPoint.distanceToPoint(Position) + increment;
  QVector3D norm_displacement = (Position - FocusPoint).normalized();
  QVector3D new_Position = FocusPoint + norm_displacement * distance;
  if (new_Position == QVector3D(0,0,0)) return;
  Position = new_Position;
  CameraData new_data = {
    QPoint(0,0),
    QPoint(0,0),
    0,
    0,
    0,
    speed,
    FocusPoint,
    Position
  };
  emit dataUpdated(new_data);
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
  speed = newSpeed;
}

void Camera::setSensitivity(float newSensitivity)
{
  sensitivity = newSensitivity;
}

void Camera::processFreeMode(QPoint ePos)
{
    if (!LMBPressed) return;

    // Stores the coordinates of the cursor
    double mouseX = ePos.rx();
    double mouseY = ePos.ry();

    // Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
    // and then "transforms" them into degrees

    float rotX = sensitivity * (float)(mouseY - (vh / 2)) / vh;
    float rotY = sensitivity * (float)(mouseX - (vw / 2)) / vw;

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
    CameraData new_data = {
      mCenterPos,
      ePos,
      rotX,
      rotY,
      angle,
      speed,
      Orientation,
      Position
    };
    emit dataUpdated(new_data);
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

