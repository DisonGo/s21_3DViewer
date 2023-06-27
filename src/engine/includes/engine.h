#ifndef ENGINE_H
#define ENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include "E/Camera.h"
#include "E/Object3D.h"
#include "Parsers/EdgeParser.h"
#include "Parsers/TriangleParser.h"
#include "Shader.h"
class Engine : protected QOpenGLFunctions {
 public:
  Engine();
  virtual ~Engine();

  void drawGeometry(GLenum type);
  int indicesN = 0;
  int verticesN = 0;
  void importObj(QString fileName);
  Camera* GetCurrentCamera();
    void SetParser(s21::BaseParser* parser);
 private:
  Camera* current_camera_ = nullptr;
  s21::BaseParser* OBJParser_ = nullptr;
  std::vector<EObject*> engine_objects_;
  std::vector<Camera*> cameras_;
  std::vector<Object3D*> objects_3d_;
  std::vector<Shader*> shaders_;
};

#endif  // ENGINE_H
