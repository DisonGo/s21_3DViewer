#ifndef GLBUFFER_H
#define GLBUFFER_H
#include "GLObject.h"
namespace s21 {
class GLBuffer : public GLObject {
 public:
  GLBuffer() { glGenBuffers(1, &ID_); };
  GLBuffer(const GLBuffer& other) {
    *this = other;
  }
  GLBuffer(GLBuffer&& other) {
    *this = other;
  }
  GLBuffer& operator=(const GLBuffer& other) {
    if (this == &other) return *this;
    if (!other.allocated_) return *this;
    allocated_ = other.allocated_;
    size_ = other.size_;
    CopyBuffer(other);
    return *this;
  }
  GLBuffer& operator=(GLBuffer&& other){
    if (this == &other) return *this;
    ID_ = other.ID_;
    allocated_ = other.allocated_;
    size_ = other.size_;
    other.ID_ = 0;
    return *this;
  };
  void CopyBuffer(const GLBuffer& other) {
    glBindBuffer(GL_COPY_READ_BUFFER, other.ID_);
    glBindBuffer(GL_COPY_WRITE_BUFFER, ID_);
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0,
                        other.allocated_);
    glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
    glBindBuffer(GL_COPY_READ_BUFFER, 0);
  };
  ~GLBuffer() { glDeleteBuffers(1, &ID_); };
  void Bind() override { glBindBuffer(GetType(), ID_); };
  void Unbind() override { glBindBuffer(GetType(), 0); };
  void Delete() override { glDeleteBuffers(1, &ID_); };
  virtual GLenum GetType() const { return type; };
  GLenum type = GL_ELEMENT_ARRAY_BUFFER;

 protected:
  size_t allocated_ = 0;
  size_t size_ = 0;
};
}  // namespace s21

#endif  // GLBUFFER_H
