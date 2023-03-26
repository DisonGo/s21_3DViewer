#include "camera.h"
#include "QtMath"
Camera::Camera(QObject *parent) : QObject(parent)
{
  setVh(0);
  setVw(0);
  setPosition(QVector3D(0,0,0));
}
Camera::Camera(int width, int height, QVector3D position, QObject *parent) : QObject(parent) {
  setVw(width);
  setVh(height);
  setPosition(position);
}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader &shader, const char *uniform)
{
  // Initializes matrices since otherwise they will be the null matrix
    QMatrix4x4 view, projection;
    baseSpeed = abs(farPlane - nearPlane) / 1000;
    view.setToIdentity();
    projection.setToIdentity();
    // Makes camera look in the right direction from the right position
    view.lookAt(Position, Position + Orientation, Up);
    // Adds perspective to the scene
    projection.perspective(qDegreesToRadians(FOVdeg), (float)vw / vh, nearPlane, farPlane);
//    qDebug() << "View mat:\n" << view << "Projection mat:\n" << projection;
    // Exports the camera matrix to the Vertex Shader
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, (projection * view).constData());
}

void Camera::keyPressSlot(QKeyEvent *e)
{
  int key = e->key();
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
  if (key == Qt::Key_Shift)
    setSpeed(baseSpeed * multiSpeed);
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
  if (!LMBPressed) return;

  // Stores the coordinates of the cursor
//  QPoint relevantMPos = e->pos() - mCenterPos;
  QPoint relevantMPos = e->pos();
  double mouseX = relevantMPos.rx();
  double mouseY = relevantMPos.ry();

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
  if (abs(angle - qDegreesToRadians(90.0f)) <= qDegreesToRadians(85.0f))
  {
    qDebug() << true;
    Orientation = newOrientation;
  }
  rotationMatrix.setToIdentity();
  rotationMatrix.rotate(-rotY, Up);

  // Rotates the Orientation left and right

  Orientation = rotationMatrix.map(Orientation);
  CameraData new_data = {
    mCenterPos,
    relevantMPos,
    rotX,
    rotY,
    angle,
    speed,
    Orientation,
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

