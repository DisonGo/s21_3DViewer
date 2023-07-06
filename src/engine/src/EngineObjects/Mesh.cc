#include "E/Mesh.h"

#include <iostream>

#include "GL/VBO.h"

std::vector<VertexData> reassembleVertexArray(std::vector<Vertex> old_arr) {
  std::vector<VertexData> new_arr;
  for (auto& vertex : old_arr) new_arr.push_back({vertex});
  return new_arr;
}
std::vector<Face> TriangleToPolygon(std::vector<TriangleFace> faces) {
  std::vector<Face> new_faces;
  for (auto& triangle : faces) {
    new_faces.push_back(
        {{triangle.indices[0], triangle.indices[1], triangle.indices[2]}});
  }
  return new_faces;
}
Mesh::Mesh() {
  initializeOpenGLFunctions();
  draw_config_ = &DrawConfig::Instance();
}

Mesh::Mesh(const s21::OBJ &obj) : Mesh()
{
  auto imp = new s21::OBJImportWireframeStrategy;
  Import(obj, imp);
  delete imp;
}

Mesh::~Mesh() {
  qDebug() << "Destroying mesh:";
  for (auto const& [key, val] : VAOmap_) {
    if (!val) continue;
    qDebug() << "Vertex Array: " << val->ID_ << " destroyed";
    delete val;
  }
}

void Mesh::Draw(GLenum type) {
  for (auto const& [key, val] : VAOmap_) {
    if (!val) continue;
    val->Bind();
    glDrawElements(type, val->GetIndicesN(), GL_UNSIGNED_INT, 0);
    val->Unbind();
  }
}

void Mesh::Import(const s21::OBJ& obj, s21::OBJImportStrategy* importer) {
  if (!importer) {
    qDebug() << "Importer is null";
    return;
  }
  VAOmap_.insert({importer->GetType(), new VAO(importer->Import(obj))});
}
