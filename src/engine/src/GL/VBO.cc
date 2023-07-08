#include "GL/VBO.h"
namespace s21 {
VBO::VBO(std::vector<VertexData> vertices) { BindVertices(vertices); }

void VBO::BindVertices(std::vector<VertexData> vertices) {
  if (ID_ == (GLuint)-1) return;
  Bind();
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexData),
               vertices.data(), GL_STATIC_DRAW);
}
}  // namespace s21
