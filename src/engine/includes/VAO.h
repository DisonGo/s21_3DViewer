#ifndef VAO_H_
#define VAO_H_
#include "GL/GLArray.h"
#include "VBO.h"
class VAO : public GLArray {
 public:
  void LinkAttrib(VBO &VBO, GLuint layout, GLuint nComponents, GLenum type,
                  GLsizeiptr stride, void *offset);
};
#endif  // !VAO_H_
