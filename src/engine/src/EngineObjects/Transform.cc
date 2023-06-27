#include "E/Transform.h"
bool Transform::operator==(const Transform& a) const {
  return (translate == a.translate && rotation == a.rotation &&
          scale == a.scale);
}
void Transform::UpdateModel() {
  modelTranslate.setToIdentity();
  modelScale.setToIdentity();
  modelRot.setToIdentity();

  modelTranslate.translate(translate);
  modelScale.scale(scale);

  modelRot.rotate(rotation.x(), 1, 0, 0);
  modelRot.rotate(rotation.y(), 0, 1, 0);
  modelRot.rotate(rotation.z(), 0, 0, 1);

  awaitingLoadInShader_ = true;
}
void Transform::LoadModelMatrix(Shader* shader) {
//  if (!awaitingLoadInShader_) return;
  if (!shader) return;
  int modelLoc = glGetUniformLocation(shader->ID, "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE,
                     (modelTranslate * modelRot * modelScale).data());
  awaitingLoadInShader_ = false;
}
