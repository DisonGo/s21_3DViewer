#include "Engine.h"

#include <memory.h>

#include <QRandomGenerator>
#include <QVector2D>
#include <QVector3D>
#include <functional>
#include <QFileInfo>
#define GET_VEC_COLOR(x) x.redF(), x.greenF(), x.blueF()
namespace s21 {
Engine::Engine() {
  initializeOpenGLFunctions();
  drawConfig_ = &DrawConfig::Instance();
  Camera* default_camera = new Camera();
  SetParser(new OBJParser);
  cameras_.push_back(default_camera);
  engine_objects_.push_back(default_camera);
  current_camera_ = default_camera;
  eObjectModel_.AddItem(default_camera, nullptr, "Main camera");
  auto program = Program::Default();
  auto plane = static_cast<Object3D*>(new Plane(100, 100, 100, 100));
  plane->SetProgram(*program);
  plane->GetTrasform().SetRotation({90, 0, 0});
  engine_objects_.push_back(plane);
  eObjectModel_.AddItem(plane,nullptr, "Plane");
  objects_3d_.push_back(plane);
  programs_.push_back(program);
}

Engine::~Engine() {
  for (auto obj : engine_objects_) delete obj;
  for (auto program : programs_) delete program;
}

Object3D* Engine::GenerateObject(QString fileName) {
  static OBJImportWireframeStrategy wireframeImporter;
  static OBJImportStandartStrategy standartImporter;
  static OBJImportTriangleStrategy triangleImporter;
  static OBJImportVertexOnlyStrategy vertexOnlyImporter;

  auto object_3d = new Object3D();
  auto obj = OBJParser().Parse(fileName.toStdString());

  object_3d->UploadMesh(*obj, &standartImporter);
  object_3d->UploadMesh(*obj, &standartImporter);
  object_3d->UploadMesh(*obj, &wireframeImporter);
  object_3d->UploadMesh(*obj, &triangleImporter);
  object_3d->UploadMesh(*obj, &vertexOnlyImporter);

  delete obj;
  return object_3d;
}

void Engine::importObj(QString fileName) {
  Object3D* object_3d = GenerateObject(fileName);
  if (!object_3d) return;
  QFileInfo fileInfo(fileName);

  auto program = Program::Default();
  object_3d->SetProgram(*program);
  objects_3d_.push_back(object_3d);
  eObjectModel_.AddItem(object_3d, nullptr, fileInfo.baseName().toStdString());
  engine_objects_.push_back(object_3d);
  programs_.push_back(program);
}

void Engine::Cycle() {
  glClearColor(GET_VEC_COLOR(drawConfig_->back_color), 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  if (drawConfig_->points) DrawGeometry(GL_POINTS);
  if (drawConfig_->lines) DrawGeometry(GL_LINES);
  if (drawConfig_->triangles) DrawGeometry(GL_TRIANGLES);
  if (drawConfig_->triangles_strip) DrawGeometry(GL_TRIANGLE_STRIP);
}

Camera* Engine::GetCurrentCamera() { return current_camera_; }

void Engine::SetParser(BaseParser* parser) {
  if (OBJParser_) delete OBJParser_;
  OBJParser_ = parser;
}

Engine* Engine::Instance() {
  static Engine instance;
  return &instance;
}

void Engine::DrawGeometry(GLenum type) {
  // p.Draw(type, current_camera_);
  for (auto object : objects_3d_)
    if (object) object->Draw(type, current_camera_);
}
}  // namespace s21
