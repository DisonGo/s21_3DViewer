#include "E/Transform.h"
namespace s21 {
void Transform::SetScale(const Vector3D &newScale) {
  scale_ = newScale;
  UpdateScale();
}
void Transform::SetRotation(const Vector3D &newRotation) {
  rotation_ = newRotation;
  UpdateRotation();
}
void Transform::SetTranslate(const Vector3D &newTranslate) {
  translate_ = newTranslate;
  UpdateTranslate();
}
const Vector3D &Transform::GetScale() const { return scale_; }
const Vector3D &Transform::GetRotation() const { return rotation_; }
const Vector3D &Transform::GetTranslate() const { return translate_; }
}  // namespace s21