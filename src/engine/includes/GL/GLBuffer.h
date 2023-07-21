#ifndef GLBUFFER_H
#define GLBUFFER_H
#include "GLObject.h"
namespace s21 {
class GLBuffer : public GLObject {
 public:
  GLBuffer() { glGenBuffers(1, &ID_); }
  ~GLBuffer() { glDeleteBuffers(1, &ID_); }
  void Bind() override { glBindBuffer(GetType(), ID_); }
  void BindBase(GLuint base) { glBindBufferBase(GetType(), base, ID_); }
  void BindData(GLsizeiptr size, const void* data,
                GLenum usage = GL_STATIC_DRAW) {
    Bind();
    glBufferData(ID_, size, data, usage);
  };
  void BufferSubData(GLintptr offset, GLsizeiptr size, const void* data) {
    glBufferSubData(ID_, offset, size, data);
  };
  void Unbind() override { glBindBuffer(GetType(), 0); }
  void Delete() override { glDeleteBuffers(1, &ID_); }
  virtual GLenum GetType() { return type; }

 private:
  GLenum type = GL_ELEMENT_ARRAY_BUFFER;
};
}  // namespace s21

#endif  // GLBUFFER_H
