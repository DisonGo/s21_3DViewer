#include "E/Transform.h"
namespace s21 {
void Transform::SetScale(const QVector3D &newScale) {
  scale_ = newScale;
  UpdateScale();
}
void Transform::SetRotation(const QVector3D &newRotation) {
  rotation_ = newRotation;
  UpdateRotation();
}
void Transform::SetTranslate(const QVector3D &newTranslate) {
  translate_ = newTranslate;
  UpdateTranslate();
}
const QVector3D &Transform::GetScale() const { return scale_; }
const QVector3D &Transform::GetRotation() const { return rotation_; }
const QVector3D &Transform::GetTranslate() const { return translate_; }
}  // namespace s21