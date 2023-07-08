#ifndef GLBUFFER_H
#define GLBUFFER_H
#include "GLObject.h"
namespace s21 {
class GLBuffer : public GLObject {
 public:
  GLBuffer() { glGenBuffers(1, &ID_); };
  ~GLBuffer() { glDeleteBuffers(1, &ID_); };
  void Bind() override { glBindBuffer(GetType(), ID_); };
  void Unbind() override { glBindBuffer(GetType(), 0); };
  void Delete() override { glDeleteBuffers(1, &ID_); };
  virtual GLenum GetType() { return type; };
  GLenum type = GL_ELEMENT_ARRAY_BUFFER;
};
}  // namespace s21

#endif  // GLBUFFER_H
