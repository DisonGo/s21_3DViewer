#include "engine.h"

#include <QRandomGenerator>
#include <QVector2D>
#include <QVector3D>

// VertexColor getRandRGB() {
//   VertexColor color;
//   color.r = QRandomGenerator::global()->generateDouble();
//   color.g = QRandomGenerator::global()->generateDouble();
//   color.b = QRandomGenerator::global()->generateDouble();
//   return color;
// }

Engine::Engine() {
  initializeOpenGLFunctions();
  Camera* default_camera = new Camera();
  cameras_.push_back(default_camera);
  engine_objects_.push_back(default_camera);
  current_camera_ = default_camera;
}

Engine::~Engine() {
  for (auto obj : engine_objects_) delete obj;
}

void Engine::importObj(QString fileName) {
  OBJ obj = ObjParser::Parse(fileName.toStdString());
  indicesN += obj.vertices.size();
  Mesh* mesh = new Mesh(obj);
  meshes_.push_back(mesh);
  engine_objects_.push_back(mesh);
}

Camera* Engine::GetCurrentCamera() { return current_camera_; }

std::vector<Transform*> Engine::GetMeshTransforms() {
  size_t size = meshes_.size();
  std::vector<Transform*> result;
  for (size_t i = 0; i < size; i++)
    result.push_back(meshes_[i]->GetTransformLink());
  return result;
}

std::vector<Mesh*> Engine::GetMeshes() { return meshes_; }

void Engine::drawGeometry(GLenum type) {
  for (auto mesh : meshes_)
    if (mesh) mesh->Draw(type, current_camera_);
}
