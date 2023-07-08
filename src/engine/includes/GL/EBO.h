#ifndef EBO_H
#define EBO_H
#include "GL/GLBuffer.h"
#include "Types/Face.h"
namespace s21 {
class EBO : public GLBuffer {
 public:
  EBO(std::vector<Face> indices);
  GLsizei GetSize();
  void BindIndices(std::vector<Face> indices);
  GLenum GetType() override { return type; };
  GLenum type = GL_ELEMENT_ARRAY_BUFFER;

 private:
  GLsizei allocated_ = 0;
  GLuint size_ = 0;
};
}  // namespace s21

#endif  // EBO_H
