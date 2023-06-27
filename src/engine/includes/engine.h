#ifndef ENGINE_H
#define ENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include "Mesh.h"
#include "ObjParser.h"
#include "Camera.h"
class Engine : protected QOpenGLFunctions {
 public:
  Engine();
  virtual ~Engine();

  void drawGeometry(GLenum type);
  int indicesN = 0;
  int verticesN = 0;
  void importObj(QString fileName);
  Camera* GetCurrentCamera();
  std::vector<Transform*> GetMeshTransforms();
  std::vector<Mesh*> GetMeshes();

 private:
  Camera* current_camera_ = nullptr;
  std::vector<EObject*> engine_objects_;
  std::vector<Camera*> cameras_;
  std::vector<Mesh*> meshes_;
};

#endif  // ENGINE_H
