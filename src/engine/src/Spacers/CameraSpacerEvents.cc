#include "Spacers/CameraSpacer.h"
namespace s21 {
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
}  // namespace s21