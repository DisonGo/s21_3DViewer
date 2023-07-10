#include "E/Transform.h"
namespace s21 {
bool Transform::operator==(const Transform &a) const {
  return (translate_ == a.translate_ && rotation_ == a.rotation_ &&
          scale_ == a.scale_);
}
void Transform::UpdateScale() {
  modelScale_.setToIdentity();
  modelScale_.scale(scale_);
  awaitingLoadInProgram_ = true;
}

void Transform::UpdateRotation() {
  modelRot_.setToIdentity();
  modelRot_.rotate(rotation_.x(), 1, 0, 0);
  modelRot_.rotate(rotation_.y(), 0, 1, 0);
  modelRot_.rotate(rotation_.z(), 0, 0, 1);
  awaitingLoadInProgram_ = true;
}

void Transform::UpdateTranslate() {
  modelTranslate_.setToIdentity();
  modelTranslate_.translate(translate_);
  awaitingLoadInProgram_ = true;
}

void Transform::UpdateModel() {
  UpdateScale();
  UpdateRotation();
  UpdateTranslate();
}
void Transform::LoadModelMatrix(Program *program) {
  if (!awaitingLoadInProgram_) return;
  if (!program) return;
  int modelLoc = program->GetUniform("model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE,
                     (modelTranslate_ * modelRot_ * modelScale_).data());
  awaitingLoadInProgram_ = false;
}
}  // namespace s21
