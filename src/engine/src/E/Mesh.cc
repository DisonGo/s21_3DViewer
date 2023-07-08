#include "E/Mesh.h"

#include <iostream>

#include "GL/VBO.h"
namespace s21 {
Mesh::Mesh() {
  initializeOpenGLFunctions();
  draw_config_ = &DrawConfig::Instance();
}

Mesh::Mesh(const s21::OBJ& obj) : Mesh() {
  auto imp = new s21::OBJImportWireframeStrategy;
  Import(obj, imp);
  delete imp;
}

Mesh::~Mesh() {
  qDebug() << "Destroying mesh:";
  for (auto const& [key, val] : VAO_map_) {
    if (!val) continue;
    qDebug() << "Vertex Array: " << val->ID_ << " destroyed";
    delete val;
  }
}

void Mesh::Draw(GLenum type) {
  for (auto const& x : VAO_map_) {
    auto key = x.first;
    auto vao = x.second;
    if (buffer_toggle_.find(key) == buffer_toggle_.end()) continue;
    if (buffer_toggle_.at(key)) {
      vao->Bind();
      if (vao->GetDrawArrays())
        glDrawArrays(type, 0, vao->GetVerticesN());
      else
        glDrawElements(type, vao->GetIndicesN(), GL_UNSIGNED_INT, 0);
      vao->Unbind();
    }
  }
}

void Mesh::Import(const s21::OBJ& obj, s21::OBJImportStrategy* importer) {
  if (!importer) {
    qDebug() << "Importer is null";
    return;
  }
  VAO_map_.insert({importer->GetType(), new VAO(importer->Import(obj))});
}

void Mesh::SetBufferToggle(OBJImportStrategyType type, bool value)
{
  auto it = buffer_toggle_.find(type);
  if (it == buffer_toggle_.end()) return;
  it->second = value;
}

bool Mesh::GetBufferToggle(OBJImportStrategyType type)
{
  auto it = buffer_toggle_.find(type);
  if (it == buffer_toggle_.end()) return false;
  return it->second;
}
}  // namespace s21
