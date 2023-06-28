#ifndef ENGINE_H
#define ENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include "E/Camera.h"
#include "E/Object3D.h"
#include "Parsers/EdgeParser.h"
#include "Parsers/TriangleParser.h"
#include "DrawConfig.h"
#include "Shader.h"
class Engine : protected QOpenGLFunctions {
 public:
  void drawGeometry(GLenum type);
  int indicesN = 0;
  int verticesN = 0;
  void importObj(QString fileName);

  void Cycle();

  Camera* GetCurrentCamera();
  void SetParser(s21::BaseParser* parser);
  static Engine* Instance();

 private:
  Engine();
  Engine(const Engine& old);                   // disallow copy constructor
  const Engine& operator=(const Engine& old);  // disallow assignment operator
  ~Engine();
  DrawConfig* drawConfig_{};
  Object3D* GetObjectTriangle(QString fileName);
  Object3D* GetObjectEdge(QString fileName);
  Camera* current_camera_ = nullptr;
  s21::BaseParser* OBJParser_ = nullptr;
  std::vector<EObject*> engine_objects_;
  std::vector<Camera*> cameras_;
  std::vector<Object3D*> objects_3d_;
  std::vector<Shader*> shaders_;
};

#endif  // ENGINE_H
