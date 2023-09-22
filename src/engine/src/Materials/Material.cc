#include "Materials/Material.h"
namespace s21 {

void Material::LoadMaterial() {
  program_->Uniform1i("u_texture_on", texture_on);

  auto is_circle = point_display_method == PointDisplayType::kCircle;
  auto is_dashed = line_display_type == LineDisplayType::kDashed;
  program_->Uniform1i("u_texture_on", texture_on);
  program_->Uniform1i("u_flat_shade", object_display_type == kFlatShading);
  program_->Uniform1i("u_do_lighting", lighting_on);
  program_->Uniform1i("u_dashed", is_dashed);
  program_->Uniform1i("u_circlePoint", is_circle);
  program_->Uniform1f("u_pointSize", vertices_size);
  program_->Uniform1i("u_dashSize", 3);
  program_->Uniform1i("u_gapSize", 3);
}

void Material::LoadCamera(Camera& camera) { camera.Matrix(*program_.get()); }

void Material::LoadModelMatrix(Transform& transform) {
  transform.LoadModelMatrix(program_.get());
}

void Material::LoadPrototypeColor(GLenum type) {
  godison::vectors::Vector3D c;
  if (type == GL_POINTS) c = vertices_color;
  if (type == GL_LINES) c = edges_color;
  if (type == GL_TRIANGLES) c = base_color;
  c /= 255;
  program_->Uniform3f("u_prototype_color", c.X(), c.Y(), c.Z());
}

void Material::LoadTexture(Texture &texture, const std::string &uniform)
{
    texture.LoadInProgram(*program_.get(), uniform);
}

void Material::SetBoolUniform(bool value, const std::string &uniform)
{
   SetIntUniform(value, uniform);
}
void Material::SetIntUniform(int value, const std::string &uniform)
{
    program_->Uniform1i(uniform, value);
}
void Material::SetFloatUniform(float value, const std::string &uniform)
{
    program_->Uniform1f(uniform, value);
}

void Material::ResetBools() {
  program_->Uniform1i("u_flat_shade", false);
  program_->Uniform1i("u_do_lighting", false);
  program_->Uniform1i("u_dashed", false);
  program_->Uniform1i("u_circlePoint", false);
}

void Material::Activate() {
  if (!program_) throw "Material program = nullptr";
  program_->Activate();
}

}  // namespace s21
