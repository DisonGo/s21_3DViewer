#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include "shader.h"
#include "Buffers.h"
extern "C" {
#include "obj_parser.h"
}
class GeometryEngine : protected QOpenGLFunctions
{
public:
  GeometryEngine(Shader *program);
  virtual ~GeometryEngine();

  void drawGeometry(GLenum type);
  int indicesN = 0;
  int verticesN = 0;
  Scene scene = {0};
private:
  Shader* program = nullptr;
  std::vector<EBO> EBOS;
  void initCubeGeometry();
  void importObj(QString fileName);
  void loadData(GLfloat *vertices, int vertCount, GLuint* indices, int indCount);
  void loadScene(Scene* new_scene);
  VAO vertexBuf;
};

#endif // GEOMETRYENGINE_H
