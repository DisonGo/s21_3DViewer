#ifndef GLBUFFER_H
#define GLBUFFER_H
#include "GLObject.h"
class GLBuffer : public GLObject {
 public:
  GLBuffer() { glGenBuffers(1, &ID); };
  ~GLBuffer() { Delete(); };
  void Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); };
  void Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); };
  void Delete() { glDeleteBuffers(1, &ID); };
};

#endif  // GLBUFFER_H
