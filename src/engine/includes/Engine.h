#ifndef ENGINE_H
#define ENGINE_H

#include <Logger.h>

#include <QOpenGLFunctions>

#include "DrawConfig.h"
#include "E/Camera.h"
#include "E/EObjectItemModel.h"
#include "E/Light/LightObject.h"
#include "E/Object3D.h"
#include "E/Object3DFactory.h"
#include "E/Plane.h"
#include "E/Point.h"
#include "Parsers/OBJParser.h"
#include "Shaders/Program.h"

namespace s21 {
class Engine : protected QOpenGLFunctions {
 public:
  Engine() = delete;
  Engine(DrawConfig& config);
  Engine(const Engine& other) : draw_config_(other.draw_config_) {
    *this = other;
  }

  Engine(Engine&& other) : draw_config_(other.draw_config_) { *this = other; }

  Engine& operator=(const Engine& other);
  Engine& operator=(Engine&& other);
  ~Engine();
  void Initialize();
  void ImportOBJFile(std::string file_path);
  void Cycle();

  EObjectItemModel& GetEObjectItemModel() { return e_object_model_; };
  Camera* GetCurrentCamera();
  std::string GetObject3DFileName(size_t index);
  std::pair<unsigned long, unsigned long> GetObject3DStats(size_t index);
  void SetCurrentCamera(Camera* camera);

 private:
  void Wipe3DObjects();
  void SetupFocusPoint();
  void CheckOpenGLSettings();
  void SetupDefaultCameras();
  void SetupObject3DFactory();
  void SetupDefaultLight();
  void CreateAndAddProgramToObject3D(Object3D& object);
  void DrawGeometry(GLenum type);
  void RemoveObject(EObject* object);
  void DefaultObject3DImport(Object3D* object, bool add_to_delete_queue = true);

  Object3D* GenerateObject(std::string file_path);

  bool initialized_ = false;
  bool single_object_mode_ = true;
  Logger logger_{"Engine"};
  Point* focus_point_ = nullptr;
  Camera* current_camera_ = nullptr;
  DrawConfig& draw_config_;
  EObjectItemModel e_object_model_;  // TODO copy/move
  Object3DFactory object3d_factory_;
  std::vector<LightObject*> lights_;
  std::vector<EObject*> engine_objects_;
  std::vector<Camera*> cameras_;
  std::vector<Object3D*> objects_3d_;
  std::vector<Program*> programs_;
};
}  // namespace s21

#endif  // ENGINE_H
