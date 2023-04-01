#ifndef ENGINE_H
#define ENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include "shader.h"
#include "buffers.h"
extern "C" {
#include "obj_parser.h"
}
class Engine : protected QOpenGLFunctions
{
public:
  Engine(Shader *program);
  virtual ~Engine();

  void drawGeometry(GLenum type);
  int indicesN = 0;
  int verticesN = 0;
  Scene scene = {0};
  void importObj(QString fileName);
private:
  Shader* program = nullptr;
  void loadData(GLfloat *vertices, int vertCount, GLuint* indices, int indCount);
  void loadScene(Scene* new_scene);
  VAO vertexBuf;
};

#endif // ENGINE_H
