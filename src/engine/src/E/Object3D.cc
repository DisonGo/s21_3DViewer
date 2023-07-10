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
void Object3D::SetEdgesColor(QColor new_color) { edges_color_ = new_color; }

void Object3D::SetEdgesThickness(double new_thickness) {
  edges_thickness_ = new_thickness;
}

void Object3D::SetVerticesColor(QColor new_color) {
  vertices_color_ = new_color;
}

void Object3D::SetVerticesSize(size_t new_size) { vertices_size_ = new_size; }

void Object3D::SetDisplayMethod(int new_method) {
  display_method_ = static_cast<DisplayMethod>(new_method);
}

void Object3D::SetUIType(int new_type) {
  ui_type_ = static_cast<UIType>(new_type);
}

void Object3D::SetProgram(Program& program) { program_ = &program; }

void Object3D::SetMesh(const Mesh& mesh) { mesh_ = std::move(mesh); }
}  // namespace s21
