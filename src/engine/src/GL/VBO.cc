#include "GL/VBO.h"
namespace s21 {
VBO::VBO(std::vector<VertexData> vertices) { BindVertices(vertices); }

void VBO::BindVertices(std::vector<VertexData> vertices) {
  if (ID_ == 0) {
    logger_.Log("ID is 0", Logger::LogLevel::kError);
    return;
  }
  Bind();
  size_ = vertices.size() * 3;
  allocated_ = vertices.size() * sizeof(VertexData);
  auto log = std::string("Allocating ") + std::to_string(size_) +
             " elements with total size of " + std::to_string(allocated_) +
             " bytes";
  logger_.Log(log.c_str());
  glBufferData(GL_ARRAY_BUFFER, allocated_, vertices.data(), GL_STATIC_DRAW);
}
}  // namespace s21
