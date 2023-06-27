#ifndef VAO_H
#define VAO_H
#include "GL/GLArray.h"
#include "GL/VBO.h"
class VAO : public GLArray {
 public:
  void LinkAttrib(VBO &VBO, GLuint layout, GLuint nComponents, GLenum type,
                  GLsizeiptr stride, void *offset);
};
#endif  // VAO_H
