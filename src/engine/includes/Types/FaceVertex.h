#ifndef FACEVERTEX_H
#define FACEVERTEX_H
#include <QOpenGLFunctions>
namespace s21 {
struct FaceVertex {
  GLuint v_index, t_index, n_index;
};
}  // namespace s21
#endif  // FACEVERTEX_H
