#ifndef VBO_H
#define VBO_H
#include "GL/GLBuffer.h"
#include "Types/VertexData.h"
namespace s21 {
class VBO : public GLBuffer {
 public:
  VBO(std::vector<VertexData> vertices);
  void BindVertices(std::vector<VertexData> vertices);
  GLenum GetType() override { return type; };
  GLenum type = GL_ARRAY_BUFFER;
  size_t GetSize() { return size_; };

 private:
  size_t size_;
  size_t allocated_;
};
}  // namespace s21
#endif  // VBO_H
