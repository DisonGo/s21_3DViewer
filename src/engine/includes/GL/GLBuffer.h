#ifndef GLBUFFER_H
#define GLBUFFER_H
#include "GLObject.h"
class GLBuffer : public GLObject {
 public:
  GLBuffer() { glGenBuffers(1, &ID_); };
  ~GLBuffer() { Delete(); };
  void Bind() override { glBindBuffer(GetType(), ID_); };
  void Unbind() override { glBindBuffer(GetType(), 0); };
  void Delete() override { glDeleteBuffers(1, &ID_); };
  virtual GLenum GetType() { return type_; };
  GLenum type_ = GL_ELEMENT_ARRAY_BUFFER;
};

#endif  // GLBUFFER_H
