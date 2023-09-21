#include "Engine.h"

#include <Logger.h>
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
Engine::Engine(DrawConfig& config) : draw_config_(config) {
  logger_.Log("Engine created: waiting for initialization");
}

Engine::~Engine() {
  for (auto obj : engine_objects_)
    if (obj) delete obj;
  for (auto program : programs_)
    if (program) delete program;
  for (auto light : lights_)
    if (light) delete light;
}

void Engine::SetupFocusPoint() {
  focus_point_ = new Point();
  AddToWhitelist(focus_point_);
  DefaultObject3DImport(focus_point_);
  logger_.Log("Setup focus point");
}

void Engine::CheckOpenGLSettings() {
  const GLubyte* version = glGetString(GL_VERSION);

  auto open_gl_version =
      "OpenGL version: " + std::string(reinterpret_cast<const char*>(version));

  GLfloat lineWidthRange[2];
  glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, lineWidthRange);
  auto max_width =
      "Maximum width of a line: " + std::to_string(lineWidthRange[1]);

  int majorVersion, minorVersion;
  glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
  glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
  if (majorVersion < 4 || minorVersion < 1)
    logger_.Log(
        "Current version of OpenGL is unsupported. Please install at least "
        "OpenGL 4.1 and further",
        Logger::LogLevel::kCritical);

  logger_.Log(open_gl_version.c_str(), Logger::LogLevel::kInfo);
  logger_.Log(max_width.c_str(), Logger::LogLevel::kInfo);
}

void Engine::SetupDefaultCameras() {
  Camera* default_camera = new Camera();
  cameras_.push_back(default_camera);
  engine_objects_.push_back(default_camera);
  current_camera_ = default_camera;
  e_object_model_.AddItem(default_camera, nullptr, "Main camera");

  Camera* second_camera = new Camera();
  second_camera->SetPosition({2, 0, 0});
  second_camera->SetViewMode(Camera::ViewMode::kOrthographic);
  second_camera->SetBox(Camera::ParallelBox(2, 2, -2, -2));
  second_camera->SetZRange({-100, 100});
  cameras_.push_back(second_camera);
  engine_objects_.push_back(second_camera);
  e_object_model_.AddItem(second_camera, nullptr, "Second camera");
  logger_.Log("Setup cameras");
}

void Engine::SetupObject3DFactory() {
  object3d_factory_.SetParser(new OBJParser);
  object3d_factory_.InstallImporter(new OBJImportWireframeStrategy);
  object3d_factory_.InstallImporter(new OBJImportTriangleStrategy);
  object3d_factory_.InstallImporter(new OBJImportNormalsStrategy);
  logger_.Log("Setup Object3D factory");
}

void Engine::SetupDefaultLight() {
  CreateLightObject(Light({0, 5, 0}, {230, 230, 230}, 1.5), "Light");
  logger_.Log("Setup default light");
}
void Engine::CreateLightObject(const Light& light, const std::string& name) {
  Point* point = new Point();
  CreateAndAddProgramToObject3D(*point);
  engine_objects_.push_back(point);
  LightObject* lightObject = new LightObject(light, *point);
  lights_.push_back(lightObject);
  e_object_model_.AddItem(static_cast<Light*>(lightObject), nullptr, name);
  objects_3d_.push_back(lightObject);
  AddToWhitelist(point);
  AddToWhitelist(static_cast<Object3D*>(lightObject));
}
void Engine::CreateAndAddProgramToObject3D(Object3D& object) {
  auto program = Program::Default();
  programs_.push_back(program);
  object.SetProgram(*program);
}

void Engine::DefaultObject3DImport(Object3D* object, bool add_to_delete_queue) {
  if (!object) return;
  CreateAndAddProgramToObject3D(*object);
  objects_3d_.push_back(object);
  if (add_to_delete_queue) engine_objects_.push_back(object);
  object->SetTextureToggle(global_texture_ != nullptr);
  logger_.Log("Default imported Object3D: " + object->GetFileName());
}
void Engine::AddToWhitelist(EObject* object) {
  whitelist_objects_.insert(object);
}

void Engine::RemoveFromWhitelist(EObject* object) {
  whitelist_objects_.erase(object);
}
bool Engine::IsWhitelisted(EObject* object) const {
  return whitelist_objects_.count(object) > 0;
}
void Engine::RemoveObject(EObject* object) {
  if (!object) return;
  if (IsWhitelisted(object)) return;
  auto type = object->GetType();
  if (type == s21::kObject3D) ERASE_FROM_VECTOR(objects_3d_, object);
  if (type == s21::kCamera) ERASE_FROM_VECTOR(cameras_, object);
  ERASE_FROM_VECTOR(engine_objects_, object);
  auto tree_item = e_object_model_.FindItem(object);
  if (!tree_item) return;
  e_object_model_.DeleteItem(tree_item);
  delete object;
  std::string log("Removed object: ");
  log += std::to_string(reinterpret_cast<uintptr_t>(object));
  logger_.Log(log);
}

void Engine::Wipe3DObjects() {
  if (objects_3d_.empty()) return;
  auto copy(objects_3d_);
  for (auto& object : copy) RemoveObject(object);
}

Object3D* Engine::GenerateObject(std::string file_path) {
  return new Object3D(object3d_factory_.GetObject(file_path.c_str()));
}
void Engine::UnloadTexture() {
  {
    if (global_texture_) {
      global_texture_->Unbind();
      delete global_texture_;
    }
    global_texture_ = nullptr;
    for (auto object : objects_3d_)
      if (object && !IsWhitelisted(object)) object->SetTextureToggle(false);
  }
}
void Engine::ImportOBJFile(std::string file_path) {
  if (!initialized_) return;
  Object3D* object_3d = GenerateObject(file_path);
  if (!object_3d) return;
  QFileInfo fileInfo(file_path.c_str());
  if (single_object_mode_) Wipe3DObjects();
  DefaultObject3DImport(object_3d);
  e_object_model_.AddItem(object_3d, nullptr,
                          fileInfo.baseName().toStdString());
}
void Engine::ImportTextureFile(std::string file_path) {
  UnloadTexture();
  global_texture_ =
      new Texture(file_path, GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
  for (auto object : objects_3d_)
    if (object && !IsWhitelisted(object) &&
        object->GetObjectDisplayType() != kWireframe)
      object->SetTextureToggle(true);
}
void Engine::Cycle() {
  if (!initialized_) return;
  glClearColor(GET_VEC_COLOR(draw_config_.back_color), 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  for (auto object : objects_3d_) {
    auto program = object->GetProgram();
    if (!program) continue;
    for (size_t i = 0; i < lights_.size(); ++i)
      lights_[i]->LoadInGLSLArray(*program, "u_ligths", i);
    program->Uniform1i("u_light_count", lights_.size());
    if (!IsWhitelisted(object) && global_texture_) {
      program->Uniform1i("u_texture_on", true);
      global_texture_->LoadInProgram(*program, "u_tex_1");
    }
  }
  if (global_texture_) global_texture_->Bind();
  if (draw_config_.points) DrawGeometry(GL_POINTS);
  if (draw_config_.lines) DrawGeometry(GL_LINES);
  if (draw_config_.triangles) DrawGeometry(GL_TRIANGLES);
  if (draw_config_.triangles_strip) DrawGeometry(GL_TRIANGLE_STRIP);
  if (global_texture_) global_texture_->Unbind();
}

Camera* Engine::GetCurrentCamera() { return current_camera_; }

std::string Engine::GetObject3DFileName(size_t index) {
  std::string name = "";
  try {
    auto object = objects_3d_.at(index);
    if (object) name = object->GetFileName();
  } catch (...) {
    logger_.Log("Object doesn't exist", Logger::LogLevel::kError);
    name = "";
  }
  return name;
}

std::pair<unsigned long, unsigned long> Engine::GetObject3DStats(size_t index) {
  std::pair<unsigned long, unsigned long> stats;
  try {
    auto object = objects_3d_.at(index);
    if (object) {
      stats.first = object->CountVertices(s21::kWireframeImport);
      stats.second = object->CountIndices(s21::kWireframeImport);
    }
  } catch (...) {
    qDebug() << "Object doesn't exist";
  }
  return stats;
}

void Engine::SetCurrentCamera(Camera* camera) { current_camera_ = camera; }

Engine& Engine::operator=(const Engine& other) {
  if (this == &other) return *this;
  for (auto& obj : other.cameras_)
    if (obj) {
      if (obj == other.current_camera_) {
        auto camera = new Camera(*obj);
        current_camera_ = camera;
        cameras_.push_back(camera);
      } else {
        cameras_.push_back(new Camera(*obj));
      }
    }
  for (auto& obj : other.objects_3d_)
    if (obj) {
      if (obj == other.focus_point_) {
        auto point = new Point(*static_cast<Point*>(obj));
        focus_point_ = point;
        objects_3d_.push_back(point);
      } else {
        objects_3d_.push_back(new Object3D(*obj));
      }
    }
  for (auto& obj : other.programs_)
    if (obj) programs_.push_back(new Program(*obj));
  for (auto& obj : other.lights_)
    if (obj) lights_.push_back(new LightObject(*obj));

  for (auto& obj : cameras_) engine_objects_.push_back(obj);
  for (auto& obj : objects_3d_) engine_objects_.push_back(obj);
  draw_config_ = other.draw_config_;
  object3d_factory_ = std::move(other.object3d_factory_);
  return *this;
}
Engine& Engine::operator=(Engine&& other) {
  if (this == &other) return *this;
  initialized_ = other.initialized_;
  if (initialized_) initializeOpenGLFunctions();
  focus_point_ = nullptr;
  current_camera_ = nullptr;
  for (auto& obj : engine_objects_)
    if (obj) delete obj;
  for (auto program : programs_)
    if (program) delete program;
  for (auto light : lights_)
    if (light) delete light;
  engine_objects_.clear();
  cameras_.clear();
  objects_3d_.clear();
  programs_.clear();
  draw_config_ = other.draw_config_;
  std::swap(focus_point_, other.focus_point_);
  std::swap(current_camera_, other.current_camera_);
  std::swap(programs_, other.programs_);
  std::swap(lights_, other.lights_);
  std::swap(objects_3d_, other.objects_3d_);
  std::swap(cameras_, other.cameras_);
  std::swap(engine_objects_, other.engine_objects_);
  return *this;
}

void Engine::Initialize() {
  if (initialized_) return;
  logger_.Log("Initializing engine");
  initializeOpenGLFunctions();
  CheckOpenGLSettings();
  glEnable(GL_PROGRAM_POINT_SIZE);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  SetupObject3DFactory();
  SetupDefaultCameras();
  SetupFocusPoint();
  SetupDefaultLight();
  initialized_ = true;
  logger_.Log("Engine initialized");
}

void Engine::DrawGeometry(GLenum type) {
  if (!initialized_) return;
  if (!current_camera_) return;
  focus_point_->GetTrasform().SetTranslate(current_camera_->GetFocusPoint());
  for (auto object : objects_3d_)
    if (object) object->Draw(type, current_camera_);
}
}  // namespace s21
