#include "GL/VAO.h"
namespace s21 {
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint nComponents, GLenum type,
                     GLsizeiptr stride, void* offset) {
  if (ID_ == (GLuint)-1) return;
  VBO.Bind();
  glVertexAttribPointer(layout, nComponents, type, GL_FALSE, stride, offset);
  glEnableVertexAttribArray(layout);
  VBO.Unbind();
}
}  // namespace s21
