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
  SetParser(new s21::TriangleParser);
  cameras_.push_back(default_camera);
  engine_objects_.push_back(default_camera);
  current_camera_ = default_camera;
}

Engine::~Engine() {
  for (auto obj : engine_objects_) delete obj;
  for (auto shader : shaders_) delete shader;
}

void Engine::importObj(QString fileName) {
  Object3D* object_3d = nullptr;
  switch (OBJParser_->GetType()) {
    case s21::kEdgeParser:
      object_3d = GetObjectEdge(fileName);
      break;
    case s21::kTriangleParser:
      object_3d = GetObjectTriangle(fileName);
      break;
    default:
      throw "Engine: Parser type not selected.";
      break;
  }
  auto shader = Shader::Default();
  object_3d->SetShader(*shader);
  objects_3d_.push_back(object_3d);
  engine_objects_.push_back(object_3d);
  shaders_.push_back(shader);
}

void Engine::Cycle()
{
  glClearColor(drawConfig_->BackColor.redF(),
               drawConfig_->BackColor.greenF(),
               drawConfig_->BackColor.blueF(), 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//  qDebug() << drawConfig_->Points;
//  qDebug() << drawConfig_->Lines;
//  qDebug() << drawConfig_->Triangles;
//  qDebug() << drawConfig_->TrianglesStrip;
  if (drawConfig_->Points)
    drawGeometry(GL_POINTS);
  if (drawConfig_->Lines)
    drawGeometry(GL_LINES);
  if (drawConfig_->Triangles)
    drawGeometry(GL_TRIANGLES);
  if (drawConfig_->TrianglesStrip)
    drawGeometry(GL_TRIANGLE_STRIP);
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

Object3D* Engine::GetObjectTriangle(QString fileName) {
  auto obj = s21::TriangleParser().Parse(fileName.toStdString());
  auto object_3d = new Object3D();
  object_3d->UploadMesh(*obj);
  delete obj;
  return object_3d;
}

Object3D* Engine::GetObjectEdge(QString fileName) {
  auto obj = s21::EdgeParser().Parse(fileName.toStdString());
  auto object_3d = new Object3D();
  object_3d->UploadMesh(*obj);
  delete obj;
  return object_3d;
}

void Engine::drawGeometry(GLenum type) {
  for (auto object : objects_3d_)
    if (object) object->Draw(type, current_camera_);
}
