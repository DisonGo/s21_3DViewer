#ifndef VBO_H
#define VBO_H
#include "GL/GLBuffer.h"
#include "Types/VertexData.h"
namespace s21 {
class VBO : public GLBuffer {
 friend class VAO;
 public:
  using GLBuffer::GLBuffer;
  VBO(std::vector<VertexData> vertices);
  void BindVertices(std::vector<VertexData> vertices);
  GLenum GetType() const override { return type; };
  GLenum type = GL_ARRAY_BUFFER;
  size_t GetSize() { return size_; };
};
}  // namespace s21
#endif  // VBO_H
