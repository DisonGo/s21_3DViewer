#ifndef VBO_H_
#define VBO_H_
#include "opengl_helper.h"

class VBO : protected QOpenGLExtraFunctions {
public:
  GLuint ID = -1;
  VBO();
  VBO(std::vector<Vertex> vertices);
  void BindVertices(std::vector<Vertex> vertices);
  void Bind();
  void Unbind();
  void Delete();
  ~VBO();
};
#endif // !VBO_H_
