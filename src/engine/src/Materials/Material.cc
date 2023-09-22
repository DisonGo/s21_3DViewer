#include "Materials/Material.h"
namespace s21 {

void Material::LoadMaterial() {
  auto is_circle = point_display_method == PointDisplayType::kCircle;
  auto is_dashed = line_display_type == LineDisplayType::kDashed;
  bool_uniforms_[GL_TRIANGLES]["u_texture_on"] = texture_on;
  bool_uniforms_[GL_TRIANGLES]["u_flat_shade"] =
      object_display_type == kFlatShading;
  bool_uniforms_[GL_TRIANGLES]["u_do_lighting"] = lighting_on;
  bool_uniforms_[GL_POINTS]["u_circlePoint"] = is_circle;
  bool_uniforms_[GL_LINES]["u_dashed"] = is_dashed;
  program_->Uniform1i("u_pointSize", vertices_size);
  program_->LineWidth(edges_thickness);
  program_->Uniform1i("u_dashSize", 3);
  program_->Uniform1i("u_gapSize", 3);
}

void Material::LoadCamera(Camera &camera) { camera.Matrix(*program_.get()); }

void Material::LoadModelMatrix(Transform &transform) {
  transform.LoadModelMatrix(program_.get());
}

void Material::LoadPrototypeSettings(GLenum type) {
  godison::vectors::Vector3D c;
  if (type == GL_POINTS) c = vertices_color;
  if (type == GL_LINES) c = edges_color;
  if (type == GL_TRIANGLES) c = base_color;
  c /= 255;
  program_->Uniform3f("u_prototype_color", c.X(), c.Y(), c.Z());
  if (bool_uniforms_.count(type))
    ;
  for (auto &[uniform, value] : bool_uniforms_[type])
    program_->Uniform1i(uniform, value);
}

void Material::LoadTexture(Texture &texture, const std::string &uniform) {
  texture.LoadInProgram(*program_.get(), uniform);
}

void Material::SetBoolUniform(bool value, const std::string &uniform) {
  SetIntUniform(value, uniform);
}
void Material::SetIntUniform(int value, const std::string &uniform) {
  program_->Uniform1i(uniform, value);
}
void Material::SetFloatUniform(float value, const std::string &uniform) {
  program_->Uniform1f(uniform, value);
}

void Material::ResetBools() {
  for (auto &[prototype, values] : bool_uniforms_)
    for (auto &[uniform, value] : values) program_->Uniform1i(uniform, false);
}

void Material::Activate() {
  if (!program_) throw "Material program = nullptr";
  program_->Activate();
}

}  // namespace s21
