
#include "E/Point.h"
namespace s21 {
Point::Point(float x, float y, float z) : Point(Vector3D(x, y, z)) {}

Point::Point(const Vector3D &position) {
  CreateMesh(position);
  material_.vertices_size = 10;
  material_.texture_on = false;
  material_.lighting_on = false;
  material_.point_display_method = kCircle;
}

void Point::Draw(GLenum type, Camera *camera) {
  Q_UNUSED(type);
  if (!camera) return;
  material_.Activate();
  material_.LoadMaterial();
  material_.LoadPrototypeColor(GL_POINTS);
  material_.LoadCamera(*camera);
  material_.LoadModelMatrix(transform_);
  for (const auto& mesh : meshes_) mesh->Draw(type);
  material_.ResetBools();
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
