#include "Spacers/CameraSpacer.h"
namespace s21 {
void CameraSpacer::keyPressSlot(QKeyEvent *e) {
  int key = e->key();

  if (key == Qt::Key_Shift) camera_.SetMoveSpeed(camera_.move_speed_);
  if (camera_.mode_ == Camera::kFree) {
    Vector3D Buf = camera_.position_;
    Vector3D distance;
    Vector3D Rigth = Vector3D::Normal(camera_.orientation_, camera_.up_);
    if (key == Qt::Key_W) distance = camera_.orientation_;
    if (key == Qt::Key_A) distance = -Rigth * 0.1;
    if (key == Qt::Key_S) distance = -camera_.orientation_;
    if (key == Qt::Key_D) distance = Rigth * 0.1;
    if (key == Qt::Key_Space) distance = camera_.up_;
    if (key == Qt::Key_Control) distance = -camera_.up_;
    distance *= camera_.move_speed_;
    camera_.position_ += distance;
    if (Buf != camera_.position_) emit ConfigUpdated();
  }
  emit ConfigUpdated();
}

void CameraSpacer::keyReleaseSlot(QKeyEvent *e) { Q_UNUSED(e) }

void CameraSpacer::mousePressSlot(QMouseEvent *e) {
  Q_UNUSED(e)
  camera_.LMBPressed_ = true;
  camera_.m_center_pos_ = godison::GPoint(e->pos().x(), e->pos().y());
}

void CameraSpacer::mouseReleaseSlot(QMouseEvent *e) {
  Q_UNUSED(e)
  camera_.LMBPressed_ = false;
}

void CameraSpacer::mouseMoveSlot(QMouseEvent *e) {
  Vector2D a;
  auto b = a * .1;
  auto p = godison::GPoint(e->pos().x(), e->pos().y());
  if (camera_.mode_ == Camera::kFree) camera_.ProcessFreeMode(p);
  if (camera_.mode_ == Camera::kFocus) camera_.ProcessFocusMode(p);
  emit ConfigUpdated();
}

void CameraSpacer::wheelEventSlot(QWheelEvent *e) {
  int delta = -1 * e->angleDelta().ry();
  camera_.SetZoomFactor((delta > 0) ? 1.1f : 0.9f);
  emit ConfigUpdated();
}
}  // namespace s21
