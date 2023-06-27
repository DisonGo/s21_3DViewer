#include "GL/VAO.h"

void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint nComponents, GLenum type,
                     GLsizeiptr stride, void* offset) {
  if (ID == (GLuint)-1) return;
  VBO.Bind();
  glVertexAttribPointer(layout, nComponents, type, GL_FALSE, stride, offset);
  glEnableVertexAttribArray(layout);
  VBO.Unbind();
}
