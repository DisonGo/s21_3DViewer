#include "Engine.h"

#include <godison/Shapes.h>
#include <godison/Vectors.h>
#include <memory.h>

#include <QFileInfo>
#include <QRandomGenerator>
#include <functional>

using godison::shapes::Polygon;
using godison::vectors::Vector3D;
#define GET_VEC_COLOR(x) x.redF(), x.greenF(), x.blueF()
#define ERASE_FROM_VECTOR(vec, x) \
  vec.erase(std::remove(vec.begin(), vec.end(), x), vec.end())
namespace s21 {
Engine::Engine(DrawConfig &config) : drawConfig_(config) {}

Engine::~Engine() {
  for (auto obj : engine_objects_) delete obj;
  for (auto program : programs_) delete program;
}

void Engine::SetupFocusPoint() {
  focus_point_ = new Point();
  auto object_3d = static_cast<Object3D*>(focus_point_);
  DefaultObject3DImport(object_3d);
}

void Engine::SetupDefaultCameras() {
  Camera* default_camera = new Camera();
  cameras_.push_back(default_camera);
  engine_objects_.push_back(default_camera);
  current_camera_ = default_camera;
  eObjectModel_.AddItem(default_camera, nullptr, "Main camera");

  Camera* second_camera = new Camera();
  cameras_.push_back(second_camera);
  engine_objects_.push_back(second_camera);
  current_camera_ = second_camera;
  eObjectModel_.AddItem(second_camera, nullptr, "Second camera");
}

void Engine::SetupObject3DFactory() {
  object3d_factory_.SetParser(new OBJParser);
  object3d_factory_.InstallImporter(new OBJImportWireframeStrategy);
  object3d_factory_.InstallImporter(new OBJImportTriangleStrategy);
}

void Engine::DefaultObject3DImport(Object3D* object, bool add_to_delete_queue) {
  if (!object) return;
  auto program = Program::Default();
  object->SetProgram(*program);
  objects_3d_.push_back(object);
  programs_.push_back(program);
  if (add_to_delete_queue) engine_objects_.push_back(object);
}

void Engine::RemoveObject(EObject* object) {
  if (!object) return;
  if (object == focus_point_) return;
  auto type = object->GetType();
  if (type == s21::kObject3D) ERASE_FROM_VECTOR(objects_3d_, object);
  if (type == s21::kCamera) ERASE_FROM_VECTOR(cameras_, object);
  ERASE_FROM_VECTOR(engine_objects_, object);
  auto tree_item = eObjectModel_.FindItem(object);
  if (!tree_item) return;
  eObjectModel_.DeleteItem(tree_item);
  delete object;
}

void Engine::Wipe3DObjects() {
  if (objects_3d_.empty()) return;
  auto copy(objects_3d_);
  for (auto& object : copy) RemoveObject(object);
}

Object3D* Engine::GenerateObject(std::string file_path) {
  return new Object3D(
      object3d_factory_.GetObject(file_path.c_str()));
}

void Engine::ImportOBJFile(std::string file_path) {
  if (!initialized_) return;
  Object3D* object_3d = GenerateObject(file_path);
  if (!object_3d) return;
  QFileInfo fileInfo(file_path.c_str());
  if (single_object_mode) Wipe3DObjects();
  DefaultObject3DImport(object_3d);
  eObjectModel_.AddItem(object_3d, nullptr, fileInfo.baseName().toStdString());
}

void Engine::Cycle() {
  if (!initialized_) return;
  glClearColor(GET_VEC_COLOR(drawConfig_.back_color), 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (drawConfig_.points) DrawGeometry(GL_POINTS);
  if (drawConfig_.lines) DrawGeometry(GL_LINES);
  if (drawConfig_.triangles) DrawGeometry(GL_TRIANGLES);
  if (drawConfig_.triangles_strip) DrawGeometry(GL_TRIANGLE_STRIP);
}

Camera* Engine::GetCurrentCamera() { return current_camera_; }

void Engine::SetCurrentCamera(Camera* camera) { current_camera_ = camera; }

void Engine::Initialize()
{
  if (initialized_) return;
  initializeOpenGLFunctions();
  glEnable(GL_PROGRAM_POINT_SIZE);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  SetupObject3DFactory();
  SetupDefaultCameras();
  SetupFocusPoint();
  initialized_ = true;
}

void Engine::DrawGeometry(GLenum type) {
  if (initialized_) return;
  if (!current_camera_) return;
  focus_point_->GetTrasform().SetTranslate(current_camera_->GetFocusPoint());
  for (auto object : objects_3d_)
    if (object) object->Draw(type, current_camera_);
}
}  // namespace s21
