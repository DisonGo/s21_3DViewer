#ifndef ENGINE_H
#define ENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include "camera.h"
#include "ObjParser.h"
#include "Mesh.h"
class Engine : protected QOpenGLFunctions
{
public:
  Engine(Camera* camera);
  virtual ~Engine();

  void drawGeometry(GLenum type);
  int indicesN = 0;
  int verticesN = 0;
  void importObj(QString fileName);
  std::vector<Transform*> GetMeshTransforms();
  std::vector<Mesh*> GetMeshes();
private:
  Camera* camera = nullptr;
  std::vector<Mesh*> meshes;
};

#endif // ENGINE_H
