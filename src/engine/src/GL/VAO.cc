#include "GL/VAO.h"
namespace s21 {
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint nComponents, GLenum type,
                     GLsizeiptr stride, void* offset) {
  if (ID_ == 0) return;
  VBO.Bind();
  glVertexAttribPointer(layout, nComponents, type, GL_FALSE, stride, offset);
  glEnableVertexAttribArray(layout);
  VBO.Unbind();
}

void VAO::Draw(GLenum type) {
  Bind();
  if (draw_arrays_ || type == GL_POINTS)
    glDrawArrays(type, 0, verticesN_);
  else
    glDrawElements(type, indicesN_, GL_UNSIGNED_INT, 0);
  Unbind();
}
}  // namespace s21
