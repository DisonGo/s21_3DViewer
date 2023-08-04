
#include "E/Light/LightObject.h"

namespace s21 {
void LightObject::Draw(GLenum type, Camera* camera) {
  if (!program_ || !camera) return;
  program_->Activate();
  transform_.LoadModelMatrix(program_);
  camera->Matrix(*program_);
  float red = 1, green = 1, blue = 1;
  auto is_circle = point_display_method_ == PointDisplayType::kCircle;
  auto is_dashed = line_display_type_ == LineDisplayType::kDashed;
  auto cam_pos = camera->GetPosition();
  program_->Uniform3f("u_lightPos", cam_pos.X(), cam_pos.Y(), cam_pos.Z());
  if (type == GL_POINTS) {
    if (point_display_method_ == PointDisplayType::kNone) return;
    red = vertices_color_.redF();
    green = vertices_color_.greenF();
    blue = vertices_color_.blueF();
    program_->Uniform1i("u_circlePoint", is_circle);
    program_->Uniform1f("u_pointSize", vertices_size_);
  }
  if (type == GL_LINES) {
    red = edges_color_.redF();
    green = edges_color_.greenF();
    blue = edges_color_.blueF();
    program_->Uniform1i("u_dashed", is_dashed);
    program_->Uniform1i("u_dashSize", 3);
    program_->Uniform1i("u_gapSize", 3);
    program_->Uniform1f("u_lineWidth", edges_thickness_);
  }
  if (type == GL_TRIANGLES) {
    red = vertices_color_.redF();
    green = vertices_color_.greenF();
    blue = vertices_color_.blueF();
  }
  program_->Uniform3f("u_prototype_color", red, green, blue);
  for (const auto& mesh : meshes_) mesh->Draw(type);
  program_->Uniform1i("u_dashed", false);
  program_->Uniform1i("u_circlePoint", false);
}

}  // namespace s21
