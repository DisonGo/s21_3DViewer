#include "E/Transform.h"
namespace s21 {
bool Transform::operator==(const Transform &a) const {
  return (translate_ == a.translate_ && rotation_ == a.rotation_ &&
          scale_ == a.scale_);
}
void Transform::UpdateScale() {
  model_scale_.SetToIdentity();
  model_scale_.Scale(scale_);
  awaitingLoadInProgram_ = true;
}

void Transform::UpdateRotation() {
  godison::matrices::Matrix4x4 rot_x, rot_y, rot_z;
  rot_x.SetToIdentity();
  rot_y.SetToIdentity();
  rot_z.SetToIdentity();
  rot_x.Rotate(rotation_.X(), {1, 0, 0});
  rot_y.Rotate(rotation_.Y(), {0, 1, 0});
  rot_z.Rotate(rotation_.Z(), {0, 0, 1});
  model_rot_ = rot_x * rot_y * rot_z;
  awaitingLoadInProgram_ = true;
}

void Transform::UpdateTranslate() {
  model_translate_.SetToIdentity();
  model_translate_.Translate(translate_);
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
  program->UniformMatrix4fv(
      "u_modelMatrix", 1, GL_FALSE,
      (model_scale_ * model_rot_ * model_translate_).RawConstData());
  awaitingLoadInProgram_ = false;
}
}  // namespace s21
