#ifndef GLARRAY_H
#define GLARRAY_H
#include "GL/GLObject.h"
class GLArray : public GLObject {
 public:
  GLArray() { glGenVertexArrays(1, &ID); };
  ~GLArray() { Delete(); };
  void Bind() { glBindVertexArray(ID); };
  void Unbind() { glBindVertexArray(0); };
  void Delete() { glDeleteVertexArrays(1, &ID); };
};
#endif  // GLARRAY_H
