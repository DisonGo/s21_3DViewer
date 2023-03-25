#ifndef VAO_H_
#define VAO_H_
#include "opengl_helper.h"
#include "VBO.h"
class VAO {
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
