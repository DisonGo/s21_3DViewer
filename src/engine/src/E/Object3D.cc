#include "E/Object3D.h"
namespace s21 {
void Object3D::Draw(GLenum type, Camera* camera) {
  if (!program_ || !camera) return;
  program_->Activate();
  transform_.LoadModelMatrix(program_);
  camera->Matrix(*program_, "camMatrix");
  mesh_.Draw(type);
}

void Object3D::UploadMesh(const OBJ& obj, OBJImportStrategy* importer) {
  if (!importer) return;
  mesh_.Import(obj, importer);
}
void Object3D::SetTransform(const Transform& transform) {
  if (transform_ == transform) return;
  transform_ = transform;
  transform_.UpdateModel();
}
void Object3D::SetProgram(Program& program) { program_ = &program; }

void Object3D::SetMesh(const Mesh& mesh) { mesh_ = std::move(mesh); }
}  // namespace s21
