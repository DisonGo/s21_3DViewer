
#include "E/Point.h"
namespace s21 {
Point::Point(float x, float y, float z) : Point(Vector3D(x, y, z)) {}

Point::Point(const Vector3D &position) {
  CreateMesh(position);
  vertices_size_ = 10;
}

void Point::Draw(GLenum type, Camera *camera) {
  Q_UNUSED(type);
  if (!camera || !program_) return;
  program_->Activate();
  float red = vertices_color_.redF();
  float green = vertices_color_.greenF();
  float blue = vertices_color_.blueF();
  transform_.LoadModelMatrix(program_);
  camera->Matrix(*program_);
  program_->Uniform3f("u_prototype_color", red, green, blue);
  program_->Uniform1f("u_pointSize", vertices_size_);
  program_->Uniform1i("u_circlePoint", true);
  for (const auto &mesh : meshes_) mesh->Draw(GL_POINTS);
}

void Point::CreateMesh(const Vector3D &position) {
  OBJ obj;
  logger_.Log("Creating mesh.");
  float x = position.X(), y = position.Y(), z = position.Z();
  obj.vertices.push_back({x, y, z});
  obj.faces.push_back({{{0, 0, 0}}});
  auto importer = new OBJImportVertexOnlyStrategy;
  UploadMesh(obj, importer);
  GetMesh(0).SetBufferToggle(s21::kVertexOnlyImport, true);
  delete importer;
}

}  // namespace s21
