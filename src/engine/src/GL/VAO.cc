#include "GL/VAO.h"
namespace s21 {
void VAO::CopyVao(const VAO &other)
{
  indicesN_ = other.indicesN_;
  verticesN_ = other.verticesN_;
  draw_arrays_ = other.draw_arrays_;
  binded_ebo_ = other.binded_ebo_;
  binded_vbo_ = other.binded_vbo_;
  Bind();
  binded_ebo_.Bind();
  binded_vbo_.Bind();
  Unbind();
}

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

void VAO::BindVBO(VBO &VBO)
{
  Bind();
  VBO.Bind();
  binded_vbo_ = VBO;
}

void VAO::BindEBO(EBO &EBO)
{
  Bind();
  EBO.Bind();
  binded_ebo_ = EBO;
}
}  // namespace s21
