#include "E/Transform.h"
namespace s21 {
bool Transform::operator==(const Transform &a) const {
  return (translate_ == a.translate_ && rotation_ == a.rotation_ &&
          scale_ == a.scale_);
}
void Transform::UpdateScale() {
  modelScale_.SetToIdentity();
  modelScale_.Scale(scale_);
  awaitingLoadInProgram_ = true;
}

void Transform::UpdateRotation() {
  modelRot_.SetToIdentity();
  modelRot_.Rotate(rotation_.X(), {1, 0, 0});
  modelRot_.Rotate(rotation_.Y(), {0, 1, 0});
  modelRot_.Rotate(rotation_.Z(), {0, 0, 1});
  awaitingLoadInProgram_ = true;
}

void Transform::UpdateTranslate() {
  modelTranslate_.SetToIdentity();
  modelTranslate_.Translate(translate_);
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
  int modelLoc = program->GetUniform("u_modelMatrix");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE,
                     (modelTranslate_ * modelRot_ * modelScale_).RawConstData());
  awaitingLoadInProgram_ = false;
}
}  // namespace s21
