#include "E/Mesh.h"

#include <iostream>
#define MAP_CONTAINS(map, val) (map.find(val) != map.end())
#include "GL/VBO.h"
namespace s21 {
Mesh::Mesh() { initializeOpenGLFunctions(); }

Mesh& Mesh::operator=(const Mesh& other) {
  if (this == &other) return *this;
  name_ = other.name_;
  buffer_toggle_ = other.buffer_toggle_;
  for (auto& [key, vao] : other.VAO_map_) {
    VAO* copy_vao = vao ? new VAO(*vao) : nullptr;
    VAO_map_.insert({key, copy_vao});
  }
  return *this;
}
Mesh& Mesh::operator=(Mesh&& other) {
  if (this == &other) return *this;
  name_ = other.name_;
  buffer_toggle_ = other.buffer_toggle_;
  VAO_map_ = other.VAO_map_;
  for (auto& [key, vao] : other.VAO_map_) vao = nullptr;
  return *this;
}

Mesh::Mesh(const s21::OBJ& obj, OBJImportStrategy* importer) : Mesh() {
  auto imp = !importer ? new s21::OBJImportWireframeStrategy : importer;
  Import(obj, imp);
  if (!importer) delete imp;
}

Mesh::~Mesh() {
  for (auto const& [key, vao] : VAO_map_) {
    if (!vao) continue;
    delete vao;
  }
}

void Mesh::Draw(GLenum type) {
  // FIXME Kinda dirty code
  for (auto const& [import_type, vao] : VAO_map_) {
    if (!MAP_CONTAINS(buffer_toggle_, import_type)) continue;
    if (buffer_toggle_.at(import_type) && vao) {
      if (type != GL_POINTS) {
        if (import_type == s21::kTriangleImport && type != GL_TRIANGLES)
          continue;
        if ((import_type == s21::kWireframeImport ||
             import_type == s21::kNormalsImport) &&
            type != GL_LINES)
          continue;
      }
      vao->Draw(type);
    }
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

void Mesh::SetBufferExceptToggle(OBJImportStrategyType type, bool value) {
  for (auto& [import_type, toggle] : buffer_toggle_)
    toggle = import_type != type ? !value : value;
}

bool Mesh::GetBufferToggle(OBJImportStrategyType type) {
  if (!MAP_CONTAINS(buffer_toggle_, type)) return false;
  return buffer_toggle_.find(type)->second;
}

unsigned long Mesh::GetVertices(OBJImportStrategyType buffer_type) {
  if (!MAP_CONTAINS(VAO_map_, buffer_type)) return 0;
  auto vao = VAO_map_.find(buffer_type)->second;
  return vao ? vao->GetVerticesN() / 3 : 0;
}

unsigned long Mesh::GetIndices(OBJImportStrategyType buffer_type) {
  if (!MAP_CONTAINS(VAO_map_, buffer_type)) return 0;
  auto vao = VAO_map_.find(buffer_type)->second;
  return vao ? vao->GetIndicesN() : 0;
}
}  // namespace s21
