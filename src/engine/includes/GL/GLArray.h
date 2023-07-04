#ifndef GLARRAY_H
#define GLARRAY_H
#include "GL/GLObject.h"
class GLArray : public GLObject {
 public:
  GLArray() { glGenVertexArrays(1, &ID_); };
  ~GLArray() { glDeleteVertexArrays(1, &ID_); };
  void Bind() { glBindVertexArray(ID_); };
  void Unbind() { glBindVertexArray(0); };
  void Delete()  { glDeleteVertexArrays(1, &ID_); };
};
#endif  // GLARRAY_H
