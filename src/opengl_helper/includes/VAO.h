#ifndef VAO_H_
#define VAO_H_
#include "VBO.h"
class VAO : protected QOpenGLExtraFunctions{
public:
  GLuint ID = -1;
  VAO();
  void Bind();
  void Unbind();
  void Delete();
  ~VAO();
  void LinkAttrib(VBO &VBO, GLuint layout, GLuint nComponents, GLenum type, GLsizeiptr stride, void *offset);
};
#endif // !VAO_H_
