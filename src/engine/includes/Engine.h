#ifndef ENGINE_H
#define ENGINE_H

#include <QOpenGLFunctions>

#include "DrawConfig.h"
#include "E/Camera.h"
#include "E/EObjectItemModel.h"
#include "E/Object3D.h"
#include "Parsers/EdgeParser.h"
#include "Parsers/TriangleParser.h"
#include "Shaders/Program.h"
class Engine : protected QOpenGLFunctions {
 public:
  void drawGeometry(GLenum type);
  int indicesN_ = 0;
  int verticesN_ = 0;
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
  DrawConfig* drawConfig_{};
  s21::BaseOBJ* GenerateOBJ(QString fileName);
  Object3D* GenerateObject(QString fileName);
  Camera* current_camera_ = nullptr;
  EObjectItemModel eObjectModel_;
  s21::BaseParser* OBJParser_ = nullptr;
  std::vector<EObject*> engine_objects_;
  std::vector<Camera*> cameras_;
  std::vector<Object3D*> objects_3d_;
  std::vector<Program*> programs_;
};

#endif  // ENGINE_H
