#ifndef ENGINE_H
#define ENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include "shader.h"
#include "ObjParser.h"
#include "Mesh.h"
class Engine : protected QOpenGLFunctions
{
public:
  Engine(Shader *program);
  virtual ~Engine();

  void drawGeometry(GLenum type);
  int indicesN = 0;
  int verticesN = 0;
  void importObj(QString fileName);
private:
  std::vector<Mesh*> meshes;
  Shader* program = nullptr;
};

#endif // ENGINE_H
