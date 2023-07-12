#ifndef VAO_H
#define VAO_H
#include <string_view>

#include "GL/EBO.h"
#include "GL/GLArray.h"
#include "GL/VBO.h"
namespace s21 {
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
  void LinkAttrib(VBO& VBO, GLuint layout, GLuint nComponents, GLenum type,
                  GLsizeiptr stride, void* offset);
  void Draw(GLenum type);

  void SetIndicesN(size_t new_indicesN) { indicesN_ = new_indicesN; };
  void SetVerticesN(size_t new_verticesN) { verticesN_ = new_verticesN; };
  void SetDrawArrays(bool new_draw_arrays_) {
    draw_arrays_ = new_draw_arrays_;
  };
  size_t GetIndicesN() { return indicesN_; };
  size_t GetVerticesN() { return verticesN_; };
  size_t GetDrawArrays() { return draw_arrays_; };

 private:
  bool draw_arrays_ = false;
  size_t indicesN_;
  size_t verticesN_;
};
}  // namespace s21
#endif  // VAO_H
