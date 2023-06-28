#include "E/Transform.h"
bool Transform::operator==(const Transform &a) const {
  return (translate_ == a.translate_ && rotation_ == a.rotation_ &&
          scale_ == a.scale_);
}

const QVector3D &Transform::GetScale() const { return scale_; }
const QVector3D &Transform::GetRotation() const { return rotation_; }
const QVector3D &Transform::GetTranslate() const { return translate_; }

void Transform::SetScale(const QVector3D &newScale) { scale_ = newScale; }

void Transform::SetRotation(const QVector3D &newRotation) {
  rotation_ = newRotation;
}

void Transform::SetTranslate(const QVector3D &newTranslate) {
  translate_ = newTranslate;
}

void Transform::UpdateModel() {
  modelTranslate_.setToIdentity();
  modelScale_.setToIdentity();
  modelRot_.setToIdentity();

  modelTranslate_.translate(translate_);
  modelScale_.scale(scale_);

  modelRot_.rotate(rotation_.x(), 1, 0, 0);
  modelRot_.rotate(rotation_.y(), 0, 1, 0);
  modelRot_.rotate(rotation_.z(), 0, 0, 1);

  awaitingLoadInShader_ = true;
}
void Transform::LoadModelMatrix(Shader *shader) {
  //  if (!awaitingLoadInShader_) return;
  if (!shader) return;
  int modelLoc = glGetUniformLocation(shader->ID, "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE,
                     (modelTranslate_ * modelRot_ * modelScale_).data());
  awaitingLoadInShader_ = false;
}
