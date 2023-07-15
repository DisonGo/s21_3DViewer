
#include "E/Point.h"
namespace s21 {
Point::Point(float x, float y, float z) : Point(Vector3D(x, y, z)) {
  vertices_size_ = 10;
}

Point::Point(const Vector3D &position) { CreateMesh(position); }

void Point::Draw(GLenum type, Camera *camera) {
  Q_UNUSED(type);
  if (!camera) return;
  program_->Activate();
  float red = vertices_color_.redF();
  float green = vertices_color_.greenF();
  float blue = vertices_color_.blueF();
  transform_.LoadModelMatrix(program_);
  camera->Matrix(*program_, "u_camMatrix");
  program_->Uniform3f("u_prototype_color", red, green, blue);
  program_->Uniform1f("u_pointSize", vertices_size_);
  program_->Uniform1i("u_circlePoint", true);
  mesh_.Draw(GL_POINTS);
}

void Point::CreateMesh(const Vector3D &position) {
  OBJ obj;
  float x = position.X(), y = position.Y(), z = position.Z();
  obj.vertices.push_back({x, y, z});
  obj.faces.push_back({{{0, 0, 0}}});
  auto importer = new OBJImportVertexOnlyStrategy;
  UploadMesh(obj, importer);
  mesh_.SetBufferToggle(s21::kVertexOnlyImport, true);
  delete importer;
}

}  // namespace s21
