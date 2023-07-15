#include "Spacers/TransformSpacer.h"
namespace s21 {
const Vector3D &TransformSpacer::GetScale() const {
  return transform_.GetScale();
}
const Vector3D &TransformSpacer::GetRotation() const {
  return transform_.GetRotation();
}
const Vector3D &TransformSpacer::GetTranslate() const {
  return transform_.GetTranslate();
}

void TransformSpacer::SetScale(const Vector3D &newScale) {
  if (transform_.GetScale() == newScale) return;
  transform_.SetScale(newScale);
  emit ConfigUpdated();
}

void TransformSpacer::SetRotation(const Vector3D &newRotation) {
  if (transform_.GetRotation() == newRotation) return;
  transform_.SetRotation(newRotation);
  emit ConfigUpdated();
}

void TransformSpacer::SetTranslate(const Vector3D &newTranslate) {
  if (transform_.GetTranslate() == newTranslate) return;
  transform_.SetTranslate(newTranslate);
  emit ConfigUpdated();
}
}  // namespace s21
