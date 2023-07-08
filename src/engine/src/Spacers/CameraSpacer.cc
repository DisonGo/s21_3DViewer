#include "Spacers/CameraSpacer.h"
namespace s21 {
CameraSpacer::CameraSpacer(QObject *parent, Camera &camera)
    : QObject(parent), camera_(camera) {}

void CameraSpacer::keyPressSlot(QKeyEvent *e) {
  int key = e->key();

  if (key == Qt::Key_Shift) camera_.SetMoveSpeed(camera_.move_speed_);
  if (camera_.mode_ == Camera::kFree) {
    QVector3D Buf = camera_.position_;
    if (key == Qt::Key_W)
      camera_.position_ += camera_.move_speed_ * camera_.orientation_;
    if (key == Qt::Key_A)
      camera_.position_ +=
          camera_.move_speed_ *
          -QVector3D::normal(camera_.orientation_, camera_.up_) * 0.1;
    if (key == Qt::Key_S)
      camera_.position_ += camera_.move_speed_ * -camera_.orientation_;
    if (key == Qt::Key_D)
      camera_.position_ +=
          camera_.move_speed_ *
          QVector3D::normal(camera_.orientation_, camera_.up_) * 0.1;
    if (key == Qt::Key_Space)
      camera_.position_ += camera_.move_speed_ * camera_.up_;
    if (key == Qt::Key_Control)
      camera_.position_ += camera_.move_speed_ * -camera_.up_;
    if (Buf != camera_.position_) emit ConfigUpdated();
  }

  //  if (mode == kFocus) {
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

void CameraSpacer::keyReleaseSlot(QKeyEvent *e) { Q_UNUSED(e) }

void CameraSpacer::mousePressSlot(QMouseEvent *e) {
  Q_UNUSED(e)
  camera_.LMBPressed_ = true;
  camera_.m_center_pos_ = e->pos();
}

void CameraSpacer::mouseReleaseSlot(QMouseEvent *e) {
  Q_UNUSED(e)
  camera_.LMBPressed_ = false;
}

void CameraSpacer::mouseMoveSlot(QMouseEvent *e) {
  camera_.ProcessFreeMode(e->pos());
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

void CameraSpacer::SetLineWidth(double newLineWidth) {
  camera_.SetLineWidth(newLineWidth);
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

double CameraSpacer::GetLineWidth() { return camera_.GetLineWidth(); }
}  // namespace s21
