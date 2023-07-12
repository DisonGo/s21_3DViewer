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
  if (camera_.mode_ == Camera::kFree) camera_.ProcessFreeMode(e->pos());
  if (camera_.mode_ == Camera::kFocus) camera_.ProcessFocusMode(e->pos());
  emit ConfigUpdated();
}

void CameraSpacer::wheelEventSlot(QWheelEvent *e) {
  int delta = -1 * e->angleDelta().ry();
  camera_.SetZoomFactor((delta > 0) ? 1.1f : 0.9f);
}
}  // namespace s21
