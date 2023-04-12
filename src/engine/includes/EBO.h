#ifndef EBO_H_
#define EBO_H_
#include "opengl_helper.h"
#include "Types/Face.h"
class EBO : protected QOpenGLExtraFunctions {
public:
  GLuint ID = -1;
  EBO();
  EBO(std::vector<Face> indices);
  GLsizei Size();
  void BindIndices(std::vector<Face> indices);
  void Bind();
  void Unbind();
  void Delete();
  ~EBO();
private:
  GLsizei allocated = 0;
  GLuint size = 0;
};

#endif // !EBO_H_

