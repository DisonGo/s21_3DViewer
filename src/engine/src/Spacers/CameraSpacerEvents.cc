#include "Spacers/CameraSpacer.h"
using godison::vectors::Vector2D;
using godison::vectors::Vector3D;
namespace s21 {
void CameraSpacer::keyPressSlot(QKeyEvent *e) {
  camera_.ProcessKeyPress((Qt::Key)e->key());
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
