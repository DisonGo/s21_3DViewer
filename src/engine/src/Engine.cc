#include "Engine.h"

#include <memory.h>

#include <QRandomGenerator>
#include <QVector2D>
#include <QVector3D>
#include <functional>

// VertexColor getRandRGB() {
//   VertexColor color;
//   color.r = QRandomGenerator::global()->generateDouble();
//   color.g = QRandomGenerator::global()->generateDouble();
//   color.b = QRandomGenerator::global()->generateDouble();
//   return color;
// }

Engine::Engine() {
  initializeOpenGLFunctions();
  drawConfig_ = &DrawConfig::Instance();
  Camera* default_camera = new Camera();
  SetParser(new s21::EdgeParser);
  cameras_.push_back(default_camera);
  engine_objects_.push_back(default_camera);
  current_camera_ = default_camera;
  eObjectModel_.AddItem(default_camera);
}

Engine::~Engine() {
  for (auto obj : engine_objects_) delete obj;
  for (auto program : programs_) delete program;
}

s21::BaseOBJ* Engine::GenerateOBJ(QString fileName) {
  s21::BaseOBJ* obj = nullptr;
  switch (OBJParser_->GetType()) {
    case s21::kEdgeParser:
      obj = static_cast<s21::EdgeParser*>(OBJParser_)
                ->Parse(fileName.toStdString());
      break;
    case s21::kTriangleParser:
      obj = static_cast<s21::TriangleParser*>(OBJParser_)
                ->Parse(fileName.toStdString());
      break;
    default:
      throw "Engine: Parser type not selected.";
      break;
  }
  return obj;
}

Object3D* Engine::GenerateObject(QString fileName) {
  s21::BaseOBJ* obj = GenerateOBJ(fileName);
  auto object_3d = new Object3D();
  if (!obj) return object_3d;
  switch (obj->GetType()) {
    case s21::kBaseOBJ:
      break;
    case s21::kEdgeOBJ:
      object_3d->UploadMesh(*static_cast<s21::EdgeOBJ*>(obj));
      break;
    case s21::kTriangleOBJ:
      object_3d->UploadMesh(*static_cast<s21::TriangleOBJ*>(obj));
      break;
  }
  delete obj;
  return object_3d;
}

void Engine::importObj(QString fileName) {
  Object3D* object_3d = GenerateObject(fileName);
  if (!object_3d) return;
  auto program = Program::Default();
  object_3d->SetProgram(*program);
  objects_3d_.push_back(object_3d);
  eObjectModel_.AddItem(object_3d);
  engine_objects_.push_back(object_3d);
  programs_.push_back(program);
}

void Engine::Cycle() {
  glClearColor(drawConfig_->back_color.redF(), drawConfig_->back_color.greenF(),
               drawConfig_->back_color.blueF(), 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  if (drawConfig_->points) drawGeometry(GL_POINTS);
  if (drawConfig_->lines) drawGeometry(GL_LINES);
  if (drawConfig_->triangles) drawGeometry(GL_TRIANGLES);
  if (drawConfig_->triangles_strip) drawGeometry(GL_TRIANGLE_STRIP);
}

Camera* Engine::GetCurrentCamera() { return current_camera_; }

void Engine::SetParser(s21::BaseParser* parser) {
  if (OBJParser_) delete OBJParser_;
  OBJParser_ = parser;
}

Engine* Engine::Instance() {
  static Engine instance;
  return &instance;
}

void Engine::drawGeometry(GLenum type) {
  for (auto object : objects_3d_)
    if (object) object->Draw(type, current_camera_);
}
