#ifndef GLOBJECT_H
#define GLOBJECT_H
#define GL_SILENCE_DEPRECATION
#include <QOpenGLExtraFunctions>
#include <QOpenGLFunctions>
namespace s21 {
class GLObject : public QOpenGLExtraFunctions {
 public:
  explicit GLObject() { initializeOpenGLFunctions(); };

  GLuint ID_ = 0;

 protected:
  virtual void Bind() = 0;
  virtual void Unbind() = 0;
  virtual void Delete() = 0;
  virtual ~GLObject() = default;
};
}  // namespace s21

#endif  // GLOBJECT_H
