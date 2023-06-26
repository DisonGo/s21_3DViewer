#ifndef GLBUFFER_H
#define GLBUFFER_H
#include "GLObject.h"
class GLBuffer : public GLObject {
 public:
  GLBuffer() { glGenBuffers(1, &ID); };
  ~GLBuffer() { Delete(); };
  void Bind() override { glBindBuffer(GetType(), ID); };
  void Unbind() override { glBindBuffer(GetType(), 0); };
  void Delete() override { glDeleteBuffers(1, &ID); };
  virtual GLenum GetType() { return type; };
  GLenum type = GL_ELEMENT_ARRAY_BUFFER;
};

#endif  // GLBUFFER_H
