#ifndef UBO_H
#define UBO_H
#include "GL/GLBuffer.h"
namespace s21 {
class UBO : public GLBuffer {
 public:
  void *GetBufferData(unsigned offset,unsigned count);
  GLenum GetType() override { return type; };
  GLenum type = GL_UNIFORM_BUFFER;
};
}  // namespace s21
#endif  // UBO_H
