#ifndef EBO_H_
#define EBO_H_
#include "GL/GLBuffer.h"
#include "Types/Face.h"
class EBO : private GLBuffer {
 public:
  EBO(std::vector<Face> indices);
  GLsizei GetSize();
  void BindIndices(std::vector<Face> indices);

 private:
  GLsizei allocated_ = 0;
  GLuint size_ = 0;
};

#endif  // !EBO_H_
