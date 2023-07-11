#ifndef ENGINE_H
#define ENGINE_H

#include <QOpenGLFunctions>

#include "DrawConfig.h"
#include "E/Camera.h"
#include "E/EObjectItemModel.h"
#include "E/Object3D.h"
#include "E/Point.h"
#include "E/Plane.h"
#include "Parsers/OBJParser.h"
#include "Shaders/Program.h"
namespace s21 {
class Engine : protected QOpenGLFunctions {
 public:
  void DrawGeometry(GLenum type);
  int indicesN = 0;
  int verticesN = 0;
  void importObj(QString fileName);
  void Cycle();
  EObjectItemModel& GetEObjectItemModel() { return eObjectModel_; };
  Camera* GetCurrentCamera();
  void SetParser(s21::BaseParser* parser);
  static Engine* Instance();

 private:
  Engine();
  Engine(const Engine& old);                   // disallow copy constructor
  const Engine& operator=(const Engine& old);  // disallow assignment operator
  ~Engine();
  void SetupFocusPoint();
  DrawConfig* drawConfig_{};
  Object3D* GenerateObject(QString fileName);
  Camera* current_camera_ = nullptr;
  EObjectItemModel eObjectModel_;
  Point focus_point_;
  s21::BaseParser* OBJParser_ = nullptr;
  std::vector<EObject*> engine_objects_;
  std::vector<Camera*> cameras_;
  std::vector<Object3D*> objects_3d_;
  std::vector<Program*> programs_;
};
}  // namespace s21

#endif  // ENGINE_H
