#ifndef GLARRAY_H
#define GLARRAY_H
#include "GL/GLObject.h"
namespace s21 {
class GLArray : public GLObject {
 public:
  GLArray() { glGenVertexArrays(1, &ID_); };
  ~GLArray() { glDeleteVertexArrays(1, &ID_); };
  void Bind() override { glBindVertexArray(ID_); };
  void Unbind() override { glBindVertexArray(0); };
  void Delete() override { glDeleteVertexArrays(1, &ID_); };
};
}  // namespace s21
#endif  // GLARRAY_H
