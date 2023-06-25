#ifndef GLOBJECT_H
#define GLOBJECT_H
#include "opengl_helper.h"
class GLObject : public QOpenGLExtraFunctions {
 public:
  explicit GLObject() { initializeOpenGLFunctions(); };

  GLuint ID = -1;
 protected:
  virtual void Bind() = 0;
  virtual void Unbind() = 0;
  virtual void Delete() = 0;

 private:
};

#endif  // GLOBJECT_H
