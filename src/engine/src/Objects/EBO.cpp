#include "EBO.h"

EBO::EBO(std::vector<Face> indices) { BindIndices(indices); }

GLsizei EBO::GetSize() { return size_; }

void EBO::BindIndices(std::vector<Face> indices) {
  if (ID == (GLuint)-1) return;
  size_ = indices.size();
  allocated_ = size_ * sizeof(Face);
  Bind();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, allocated_, indices.data(),
               GL_STATIC_DRAW);
}
