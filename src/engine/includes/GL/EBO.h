#ifndef EBO_H
#define EBO_H
#include "GL/GLBuffer.h"
#include "Types/Face.h"
namespace s21 {
class EBO : public GLBuffer {
  friend class VAO;

 public:
  using GLBuffer::GLBuffer;
  EBO(std::vector<Face> indices);
  GLsizei GetSize();
  void BindIndices(std::vector<Face> indices);
  GLenum GetType() const override { return type; };
  GLenum type = GL_ELEMENT_ARRAY_BUFFER;
};
}  // namespace s21

#endif  // EBO_H
