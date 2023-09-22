#include "E/Object3D.h"

namespace s21 {
Object3D& Object3D::operator=(const Object3D& other) {
  if (this == &other) return *this;
  file_name_ = other.file_name_;
  transform_ = other.transform_;
  base_color_ = other.base_color_;
  edges_color_ = other.edges_color_;
  edges_thickness_ = other.edges_thickness_;
  vertices_color_ = other.vertices_color_;
  vertices_size_ = other.vertices_size_;
  point_display_method_ = other.point_display_method_;
  line_display_type_ = other.line_display_type_;

  program_ = other.program_;
  delete_program_ = true;

  for (auto& mesh : other.meshes_)
    meshes_.push_back(std::make_shared<Mesh>(*mesh));
  return *this;
}
Object3D& Object3D::operator=(Object3D&& other) {
  if (this == &other) return *this;
  file_name_ = other.file_name_;
  transform_ = other.transform_;
  base_color_ = other.base_color_;
  edges_color_ = other.edges_color_;
  edges_thickness_ = other.edges_thickness_;
  vertices_color_ = other.vertices_color_;
  vertices_size_ = other.vertices_size_;
  point_display_method_ = other.point_display_method_;
  line_display_type_ = other.line_display_type_;
  delete_program_ = other.delete_program_;

  std::swap(meshes_, other.meshes_);
  std::swap(program_, other.program_);
  other.program_ = nullptr;

  return *this;
}

void Object3D::Draw(GLenum type, Camera* camera) {
  if (!program_ || !camera) return;
  program_->Activate();
  transform_.LoadModelMatrix(program_);
  camera->Matrix(*program_);
  program_->Uniform1i("u_texture_on", texture_on_);
  float red = 1, green = 1, blue = 1;
  auto is_circle = point_display_method_ == PointDisplayType::kCircle;
  auto is_dashed = line_display_type_ == LineDisplayType::kDashed;
  if (type == GL_POINTS) {
    if (point_display_method_ == PointDisplayType::kNone) return;
    program_->Uniform1i("u_circlePoint", is_circle);

    red = vertices_color_.X();
    green = vertices_color_.Y();
    blue = vertices_color_.Z();
  }
  if (type == GL_LINES) {
    program_->Uniform1i("u_dashed", is_dashed);
    red = edges_color_.X();
    green = edges_color_.Y();
    blue = edges_color_.Z();
  }
  if (type == GL_TRIANGLES) {
    program_->Uniform1i("u_flat_shade", object_display_type_ == kFlatShading);
    program_->Uniform1i("u_do_lighting", lighting_on_);
    red = base_color_.X();
    green = base_color_.Y();
    blue = base_color_.Z();
  }

  program_->Uniform1f("u_pointSize", vertices_size_);
  program_->Uniform1i("u_dashSize", 3);
  program_->Uniform1i("u_gapSize", 3);
  program_->Uniform3f("u_prototype_color", red / 255, green / 255, blue / 255);
  program_->LineWidth(edges_thickness_);

  for (const auto& mesh : meshes_) mesh->Draw(type);
  program_->Uniform1i("u_flat_shade", false);
  program_->Uniform1i("u_do_lighting", false);
  program_->Uniform1i("u_dashed", false);
  program_->Uniform1i("u_circlePoint", false);
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

void Object3D::SetBaseColor(godison::vectors::Vector3D new_color) {
  base_color_ = new_color;
}

void Object3D::SetEdgesColor(godison::vectors::Vector3D new_color) {
  edges_color_ = new_color;
}

void Object3D::SetEdgesThickness(double new_thickness) {
  edges_thickness_ = new_thickness;
}

void Object3D::SetVerticesColor(godison::vectors::Vector3D new_color) {
  vertices_color_ = new_color;
}

void Object3D::SetVerticesSize(double new_size) { vertices_size_ = new_size; }

void Object3D::SetDisplayMethod(PointDisplayType new_type) {
  point_display_method_ = new_type;
}

void Object3D::SetLineDisplayType(LineDisplayType new_type) {
  line_display_type_ = new_type;
}
void Object3D::SetObjectDisplayType(ObjectDisplayType new_type) {
  object_display_type_ = new_type;
  bool is_wireframe = new_type == kWireframe;
  auto buffer_to_except = is_wireframe ? kWireframeImport : kTriangleImport;
  static bool texture_was = true;
  SetLightingToggle(!is_wireframe);
  if (!is_wireframe) texture_was = texture_on_;
  if (texture_was) SetTextureToggle(!is_wireframe);

  for (const auto& mesh : meshes_)
    mesh->SetBufferExceptToggle(buffer_to_except, true);
}
void Object3D::SetFileName(std::string file_name) { file_name_ = file_name; }
void Object3D::SetTextureToggle(bool on) { texture_on_ = on; }
void Object3D::SetLightingToggle(bool on) { lighting_on_ = on; }
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

void Object3D::SetProgram(Program& program) { program_ = &program; }
}  // namespace s21
