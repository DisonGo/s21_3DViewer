#include "E/Object3D.h"

void Object3D::Draw(GLenum type, Camera* camera) {
  if (!shader_ || !camera) return;
  shader_->Activate();
  transform_.LoadModelMatrix(shader_);
  camera->Matrix(*shader_, "camMatrix");
  mesh_.Draw(type);
}

void Object3D::UploadMesh(const s21::EdgeOBJ& obj) { mesh_.LoadObj(obj); }

void Object3D::UploadMesh(const s21::TriangleOBJ& obj) { mesh_.LoadObj(obj); }
void Object3D::SetTransform(const Transform& transform) {
  if (transform_ == transform) return;

  transform_ = transform;
  transform_.UpdateModel();
}
void Object3D::SetShader(Shader& shader) { shader_ = &shader; }

void Object3D::SetMesh(const Mesh& mesh) { mesh_ = mesh; }
