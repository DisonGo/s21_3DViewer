#ifndef VBO_H
#define VBO_H
#include "GL/GLBuffer.h"
#include "Types/VertexData.h"
namespace s21 {
class VBO : public GLBuffer {
 public:
  VBO(std::vector<VertexData> vertices);
  // VBO(std::vector<Vertex> vertices);
  // VBO(std::vector<Normal> vertices);
  // VBO(std::vector<Normal> vertices);
  void BindVertices(std::vector<VertexData> vertices);
  GLenum GetType() override { return type; };
  GLenum type = GL_ARRAY_BUFFER;
};
}  // namespace s21
#endif  // VBO_H
