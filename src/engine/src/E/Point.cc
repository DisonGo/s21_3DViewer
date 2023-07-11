
#include "E/Point.h"
namespace s21 {
Point::Point(float x, float y, float z) : Point(QVector3D(x,y,z)){}

Point::Point(const QVector3D &position)
{
  CreateMesh(position);
}

void Point::Draw(GLenum type, Camera* camera)
{
  Q_UNUSED(type);
  if (!camera) return;
  program_->Activate();
  float red = vertices_color_.redF();
  float green = vertices_color_.greenF();
  float blue = vertices_color_.blueF();
  transform_.LoadModelMatrix(program_);
  camera->Matrix(*program_, "u_camMatrix");
  glUniform3f(program_->GetUniform("u_prototype_color"), red, green, blue);
  glUniform1f(program_->GetUniform("u_pointSize"), vertices_size_);
  mesh_.Draw(GL_POINTS);
}

void Point::CreateMesh(const QVector3D &position)
{
  OBJ obj;
  float x = position.x(), y = position.y(), z = position.z();
  obj.vertices.push_back({x,y,z});
  obj.faces.push_back({{{0,0,0}}});
  auto importer = new OBJImportVertexOnlyStrategy;
  UploadMesh(obj, importer);
  mesh_.SetBufferToggle(s21::kVertexOnlyImport, true);
  delete importer;
}

}  // namespace s21
