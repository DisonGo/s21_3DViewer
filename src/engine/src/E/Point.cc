
#include "E/Point.h"
namespace s21 {
Point::Point(float x, float y, float z) : Point(Vector3D(x, y, z)) {}

Point::Point(const Vector3D &position) {
  CreateMesh(position);
  vertices_size_ = 10;
  texture_on_ = false;
}

void Point::Draw(GLenum type, Camera *camera) {
  Q_UNUSED(type);
  if (!camera || !program_) return;
  program_->Activate();
  program_->Uniform1i("u_texture_on", texture_on_);
  float red = vertices_color_.X();
  float green = vertices_color_.Y();
  float blue = vertices_color_.Z();
  transform_.LoadModelMatrix(program_);
  camera->Matrix(*program_);
  program_->Uniform3f("u_prototype_color", red / 255, green / 255, blue / 255);
  program_->Uniform1f("u_pointSize", vertices_size_);
  program_->Uniform1i("u_circlePoint", true);
  // logger_.Log("Drawing point", Logger::LogLevel::kWarning);
  for (const auto &mesh : meshes_) mesh->Draw(GL_POINTS);
}

void Point::CreateMesh(const Vector3D &position) {
  OBJ obj;
  logger_.Log("Creating mesh.", Logger::LogLevel::kWarning);
  float x = position.X(), y = position.Y(), z = position.Z();
  obj.vertices.push_back({x, y, z});
  obj.faces.push_back({{{0, 0, 0}}});
  auto importer = new OBJImportStandartStrategy;
  UploadMesh(obj, importer);
  GetMesh(0).SetBufferExceptToggle(s21::kStandartImport, true);
  delete importer;
}

}  // namespace s21
