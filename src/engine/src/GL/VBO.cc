#include "GL/VBO.h"
namespace s21 {
VBO::VBO(std::vector<VertexData> vertices) { BindVertices(vertices); }

void VBO::BindVertices(std::vector<VertexData> vertices) {
  if (ID_ == 0) return;
  Bind();
  size_ = vertices.size() * 3;
  allocated_ = vertices.size() * sizeof(VertexData);
  glBufferData(GL_ARRAY_BUFFER, allocated_, vertices.data(), GL_STATIC_DRAW);
}
}  // namespace s21
