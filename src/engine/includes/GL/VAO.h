#ifndef VAO_H
#define VAO_H
#include "GL/GLArray.h"
#include "GL/EBO.h"
#include "GL/VBO.h"
#include <string_view>
class VAO : public GLArray {
 public:
  using GLArray::GLArray;
  VAO(const VAO& other) {
    ID_ = other.ID_;
    indicesN_ = other.indicesN_;
  };
  VAO(VAO&& other) {
    ID_ = other.ID_;
    indicesN_ = other.indicesN_;
    other.ID_ = 0;
  };
  const VAO& operator=(VAO&& other) {
    ID_ = other.ID_;
    indicesN_ = other.indicesN_;
    other.ID_ = 0;
    return *this;
  };
  const VAO& operator=(const VAO& other) {
    ID_ = other.ID_;
    indicesN_ = other.indicesN_;
    return *this;
  };
  void LinkAttrib(VBO &VBO, GLuint layout, GLuint nComponents, GLenum type,
                  GLsizeiptr stride, void *offset);

  void SetIndicesN(size_t new_indicesN) {indicesN_ = new_indicesN;};
  void SetVerticesN(size_t new_verticesN) {verticesN_ = new_verticesN;};
  size_t GetIndicesN() {return indicesN_;};
  size_t GetVerticesN() {return verticesN_;};
private:
  size_t indicesN_;
  size_t verticesN_;
};
#endif  // VAO_H
