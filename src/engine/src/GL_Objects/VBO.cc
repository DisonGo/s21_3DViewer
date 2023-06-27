#include "GL/VBO.h"

VBO::VBO(std::vector<VertexData> vertices) { BindVertices(vertices); }

void VBO::BindVertices(std::vector<VertexData> vertices) {
  if (ID == (GLuint)-1) return;
  Bind();
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexData),
               vertices.data(), GL_STATIC_DRAW);
}
