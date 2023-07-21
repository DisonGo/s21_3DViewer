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
Engine::Engine() {
  initializeOpenGLFunctions();
  drawConfig_ = &DrawConfig::Instance();
  qDebug() << "Engine config:" << drawConfig_;
  SetupObject3DFactory();
  SetupDefaultCamera();
  SetupFocusPoint();
  camera_uniform_buffer_.Bind();
  camera_uniform_buffer_.BindBase(0);
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
      // Handle the error
      qDebug() << "Error binding uniform buffer to binding point: " <<
          error << "\n";
  }
  camera_uniform_buffer_.BindData(16, NULL, GL_STREAM_DRAW);
  camera_uniform_buffer_.Unbind();
  camera_uniform_buffer_.BindBufferRange(0, 0, 16);

  Camera* second_camera = new Camera();
  cameras_.push_back(second_camera);
  engine_objects_.push_back(second_camera);
  current_camera_ = second_camera;
  eObjectModel_.AddItem(second_camera, nullptr, "Second camera");
}

Engine::~Engine() {
  for (auto obj : engine_objects_) delete obj;
  for (auto program : programs_) delete program;
}

void Engine::SetupFocusPoint() {
  auto object_3d = static_cast<Object3D*>(&focus_point_);
  DefaultObject3DImport(object_3d, false);
}

void Engine::SetupDefaultCamera() {
  Camera* default_camera = new Camera();
  default_camera->SetPosition({2, 3, 4});
  cameras_.push_back(default_camera);
  engine_objects_.push_back(default_camera);
  current_camera_ = default_camera;
  eObjectModel_.AddItem(default_camera, nullptr, "Main camera");
}

void Engine::SetupObject3DFactory() {
  object3d_factory_.SetParser(new OBJParser);
  object3d_factory_.InstallImporter(new OBJImportWireframeStrategy);
  object3d_factory_.InstallImporter(new OBJImportTriangleStrategy);
}

void Engine::DefaultObject3DImport(Object3D* object, bool add_to_delete_queue) {
  if (!object) return;
  auto program = Program::Default();
  program->UniformBlockBinding("CameraData", 0);
  object->SetProgram(*program);
  objects_3d_.push_back(object);
  programs_.push_back(program);
  if (add_to_delete_queue) engine_objects_.push_back(object);
}

void Engine::RemoveObject(EObject* object) {
  if (!object) return;
  if (object == &focus_point_) return;
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

Object3D* Engine::GenerateObject(QString fileName) {
  return new Object3D(
      object3d_factory_.GetObject(fileName.toStdString().c_str()));
}

void Engine::importObj(QString fileName) {
  Object3D* object_3d = GenerateObject(fileName);
  if (!object_3d) return;
  QFileInfo fileInfo(fileName);
  if (single_object_mode) Wipe3DObjects();
  DefaultObject3DImport(object_3d);
  eObjectModel_.AddItem(object_3d, nullptr, fileInfo.baseName().toStdString());
}

void Engine::Cycle() {
  glClearColor(GET_VEC_COLOR(drawConfig_->back_color), 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  if (!current_camera_) return;
  camera_uniform_buffer_.Bind();
  focus_point_.GetTrasform().SetTranslate(current_camera_->GetFocusPoint());
  current_camera_->Matrix();
//  current_camera_->SetDefaultUBOData(&camera_uniform_buffer_);
  const float a[2] = {1, 1};
  camera_uniform_buffer_.BufferSubData(0, 8, &a[0]);
  camera_uniform_buffer_.Unbind();
  
  if (drawConfig_->points) DrawGeometry(GL_POINTS);
  if (drawConfig_->lines) DrawGeometry(GL_LINES);
  if (drawConfig_->triangles) DrawGeometry(GL_TRIANGLES);
  if (drawConfig_->triangles_strip) DrawGeometry(GL_TRIANGLE_STRIP);
  camera_uniform_buffer_.Unbind();
}

Camera* Engine::GetCurrentCamera() { return current_camera_; }

void Engine::SetCurrentCamera(Camera* camera) { current_camera_ = camera; }

Engine& Engine::Instance() {
  static Engine instance;
  return instance;
}

void Engine::DrawGeometry(GLenum type) {
  for (auto object : objects_3d_)
    if (object) object->Draw(type);
}
}  // namespace s21
