#ifndef GLARRAY_H
#define GLARRAY_H
#include "GL/GLObject.h"
class GLArray : public GLObject {
 public:
  GLArray() { glGenVertexArrays(1, &ID_); };
  ~GLArray() { qDebug() << "Deleting GLArray ID: " << ID_;
    glDeleteVertexArrays(1, &ID_); };
  void Bind() override { glBindVertexArray(ID_); };
  void Unbind() override { glBindVertexArray(0); };
  void Delete()  override { glDeleteVertexArrays(1, &ID_); };
};
#endif  // GLARRAY_H
