#include "Spacers/TransformSpacer.h"

const QVector3D &TransformSpacer::GetScale() const {
  return transform_.GetScale();
}
const QVector3D &TransformSpacer::GetRotation() const {
  return transform_.GetRotation();
}
const QVector3D &TransformSpacer::GetTranslate() const {
  return transform_.GetTranslate();
}

void TransformSpacer::SetScale(const QVector3D &newScale) {
  transform_.SetScale(newScale);
}

void TransformSpacer::SetRotation(const QVector3D &newRotation) {
  transform_.SetRotation(newRotation);
}

void TransformSpacer::SetTranslate(const QVector3D &newTranslate) {
  transform_.SetTranslate(newTranslate);
}