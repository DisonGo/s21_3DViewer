#include "Engine.h"

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
  for (auto shader : shaders_) delete shader;
}

void Engine::importObj(QString fileName) {
  OBJ obj = ObjParser::Parse(fileName.toStdString());
  indicesN += obj.vertices.size();
  auto object_3d = new Object3D();
  auto shader = Shader::Default();
  object_3d->UploadMesh(obj);
  object_3d->SetShader(*shader);
  objects_3d_.push_back(object_3d);
  engine_objects_.push_back(object_3d);
  shaders_.push_back(shader);
}

Camera* Engine::GetCurrentCamera() { return current_camera_; }

void Engine::drawGeometry(GLenum type) {
  for (auto object : objects_3d_)
    if (object) object->Draw(type, current_camera_);
}
