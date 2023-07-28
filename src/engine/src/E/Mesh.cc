#include "E/Mesh.h"

#include <iostream>
#define MAP_CONTAINS(map, val) (map.find(val) != map.end())
#include "GL/VBO.h"
namespace s21 {
Mesh::Mesh() { initializeOpenGLFunctions(); }

Mesh::Mesh(const s21::OBJ& obj, OBJImportStrategy* importer) : Mesh() {
  auto imp = !importer ? new s21::OBJImportWireframeStrategy : importer;
  Import(obj, imp);
  if (!importer) delete imp;
}

Mesh::~Mesh() {
  //  qDebug() << "Destroying mesh:";
  for (auto const& [key, vao] : VAO_map_) {
    if (!vao) continue;
    //    qDebug() << "Vertex Array: " << vao->ID_ << " destroyed";
    delete vao;
  }
}

void Mesh::Draw(GLenum type) {
  for (auto const& [import_type, vao] : VAO_map_) {
    if (!MAP_CONTAINS(buffer_toggle_, import_type)) continue;
    if (buffer_toggle_.at(import_type) && vao) vao->Draw(type);
  }
}

void Mesh::Import(const s21::OBJ& obj, s21::OBJImportStrategy* importer) {
  if (!importer) {
    qDebug() << "Importer is null";
    return;
  }
  if (!obj.name.empty()) name_ = obj.name;
  auto import_type = importer->GetType();
  auto vao = new VAO(importer->Import(obj));
  if (VAO_map_.count(import_type)) {
    delete VAO_map_[import_type];
    VAO_map_[import_type] = vao;
  } else {
    VAO_map_.insert({import_type, vao});
  }
}

void Mesh::SetBufferToggle(OBJImportStrategyType type, bool value) {
  if (!MAP_CONTAINS(buffer_toggle_, type)) return;
  buffer_toggle_.find(type)->second = value;
}

bool Mesh::GetBufferToggle(OBJImportStrategyType type) {
  if (!MAP_CONTAINS(buffer_toggle_, type)) return false;
  return buffer_toggle_.find(type)->second;
}
}  // namespace s21
