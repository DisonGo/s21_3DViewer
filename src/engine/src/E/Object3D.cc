#include "E/Object3D.h"

namespace s21 {
Object3D& Object3D::operator=(const Object3D& other) {
  if (this == &other) return *this;
  file_name_ = other.file_name_;
  transform_ = other.transform_;

  for (auto& mesh : other.meshes_)
    meshes_.push_back(std::make_shared<Mesh>(*mesh));
  return *this;
}
Object3D& Object3D::operator=(Object3D&& other) {
  if (this == &other) return *this;
  file_name_ = other.file_name_;
  transform_ = other.transform_;

  std::swap(meshes_, other.meshes_);

  return *this;
}

void Object3D::Draw(GLenum type, Camera* camera) {
  if (!camera) return;
  if (type == GL_POINTS && material_.point_display_method == kNoPoint) return;
  material_.Activate();
  material_.LoadMaterial();
  material_.LoadPrototypeSettings(type);
  material_.LoadCamera(*camera);
  material_.LoadModelMatrix(transform_);
  material_.LoadTexture("u_tex_1");
  for (const auto& mesh : meshes_) mesh->Draw(type);
  material_.ResetBools();
  material_.Deactivate();
}

void Object3D::UploadMesh(const OBJ& obj, OBJImportStrategy* importer) {
  if (!importer) return;
  bool mesh_exists = false;
  for (auto& mesh : meshes_) {
    if (mesh->GetName() == obj.name) {
      mesh_exists = true;
      mesh->Import(obj, importer);
    }
  }
  if (!mesh_exists) {
    auto mesh_ptr = std::make_shared<Mesh>(obj, importer);
    meshes_.push_back(mesh_ptr);
  }
}
void Object3D::SetTransform(const Transform& transform) {
  if (transform_ == transform) return;
  transform_ = transform;
  transform_.UpdateModel();
}

void Object3D::SetObjectDisplayType(ObjectDisplayType new_type) {
  material_.object_display_type = new_type;
  bool is_wireframe = new_type == kWireframe;
  auto buffer_to_except = is_wireframe ? kWireframeImport : kTriangleImport;
  material_.lighting_on = !is_wireframe;
  material_.texture_on = !is_wireframe;

  for (const auto& mesh : meshes_)
    mesh->SetBufferExceptToggle(buffer_to_except, true);
}
void Object3D::SetFileName(std::string file_name) { file_name_ = file_name; }
unsigned long Object3D::CountVertices(OBJImportStrategyType buffer_type) {
  unsigned long count = 0;
  for (auto& mesh : meshes_) count += mesh->GetVertices(buffer_type);
  return count;
}

unsigned long Object3D::CountIndices(OBJImportStrategyType buffer_type) {
  unsigned long count = 0;
  for (auto& mesh : meshes_) count += mesh->GetIndices(buffer_type);
  return count;
}
}  // namespace s21
