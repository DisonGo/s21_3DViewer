#include "Spacers/CameraSpacer.h"
CameraSpacer::CameraSpacer(QObject *parent, Camera &camera)
    : QObject(parent), camera_(camera) {}

void CameraSpacer::keyPressSlot(QKeyEvent *e) {
  int key = e->key();

  if (key == Qt::Key_Shift) camera_.SetMoveSpeed(camera_.moveSpeed);
  if (camera_.mode == Camera::Free) {
    QVector3D Buf = camera_.Position;
    if (key == Qt::Key_W)
      camera_.Position += camera_.moveSpeed * camera_.Orientation;
    if (key == Qt::Key_A)
      camera_.Position += camera_.moveSpeed *
                          -QVector3D::normal(camera_.Orientation, camera_.Up) *
                          0.1;
    if (key == Qt::Key_S)
      camera_.Position += camera_.moveSpeed * -camera_.Orientation;
    if (key == Qt::Key_D)
      camera_.Position += camera_.moveSpeed *
                          QVector3D::normal(camera_.Orientation, camera_.Up) *
                          0.1;
    if (key == Qt::Key_Space)
      camera_.Position += camera_.moveSpeed * camera_.Up;
    if (key == Qt::Key_Control)
      camera_.Position += camera_.moveSpeed * -camera_.Up;
    if (Buf != camera_.Position) emit ConfigUpdated();
  }

  //  if (mode == Focus) {
  //    if (!( key == Qt::Key_W
  //        || key == Qt::Key_A
  //        || key == Qt::Key_S
  //        || key == Qt::Key_D)) return;        // Rotate left around the
  //        center of rotation
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
  emit ConfigUpdated();
}

void CameraSpacer::keyReleaseSlot(QKeyEvent *e) {}

void CameraSpacer::mousePressSlot(QMouseEvent *e) {
  camera_.LMBPressed = true;
  camera_.mCenterPos = e->pos();
}

void CameraSpacer::mouseReleaseSlot(QMouseEvent *e) {
  camera_.LMBPressed = false;
}

void CameraSpacer::mouseMoveSlot(QMouseEvent *e) {
  camera_.processFreeMode(e->pos());
  emit ConfigUpdated();
}

void CameraSpacer::SetMode(Camera::CameraMode newMode) {
  camera_.SetMode(newMode);
  emit ConfigUpdated();
}

void CameraSpacer::SetViewMode(Camera::ViewMode newViewMode) {
  camera_.SetViewMode(newViewMode);
  emit ConfigUpdated();
}

void CameraSpacer::SetFocusPoint(const QVector3D &newFocusPoint) {
  camera_.SetFocusPoint(newFocusPoint);
  emit ConfigUpdated();
}

void CameraSpacer::SetPosition(const QVector3D &newPosition) {
  camera_.SetPosition(newPosition);
  emit ConfigUpdated();
}

void CameraSpacer::SetOrientation(const QVector3D &newOrientation) {
  camera_.SetOrientation(newOrientation);
  emit ConfigUpdated();
}

void CameraSpacer::SetZRange(const QVector2D &newZRange) {
  camera_.SetZRange(newZRange);
  emit ConfigUpdated();
}

void CameraSpacer::SetFOV(float newFOV) {
  camera_.SetFOV(newFOV);
  emit ConfigUpdated();
}

void CameraSpacer::SetVw(int newVw) {
  camera_.SetVw(newVw);
  emit ConfigUpdated();
}

void CameraSpacer::SetVh(int newVh) {
  camera_.SetVh(newVh);
  emit ConfigUpdated();
}

void CameraSpacer::SetMoveSpeed(float newMoveSpeed) {
  camera_.SetMoveSpeed(newMoveSpeed);
  emit ConfigUpdated();
}

void CameraSpacer::SetRotationSpeed(float newRotationSpeed) {
  camera_.SetRotationSpeed(newRotationSpeed);
  emit ConfigUpdated();
}
void CameraSpacer::SetBox(const Camera::ParallelBox &newBox) {
  camera_.SetBox(newBox);
  emit ConfigUpdated();
}

Camera::CameraMode CameraSpacer::GetMode() const { return camera_.GetMode(); }

Camera::ViewMode CameraSpacer::GetViewMode() const {
  return camera_.GetViewMode();
}

const QVector3D &CameraSpacer::GetFocusPoint() const {
  return camera_.GetFocusPoint();
}

const QVector3D &CameraSpacer::GetPosition() const {
  return camera_.GetPosition();
}

const QVector3D &CameraSpacer::GetOrientation() const {
  return camera_.GetOrientation();
}

const QVector2D &CameraSpacer::GetZRange() const { return camera_.GetZRange(); }

float CameraSpacer::GetFOV() const { return camera_.GetFOV(); }

int CameraSpacer::GetVw() const { return camera_.GetVw(); }

int CameraSpacer::GetVh() const { return camera_.GetVh(); }

float CameraSpacer::GetMoveSpeed() const { return camera_.GetMoveSpeed(); }

float CameraSpacer::GetRotationSpeed() const {
  return camera_.GetRotationSpeed();
}

const Camera::ParallelBox &CameraSpacer::GetBox() const {
  return camera_.GetBox();
}
