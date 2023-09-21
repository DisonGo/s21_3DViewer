#ifndef FACEVERTEX_H
#define FACEVERTEX_H
#include <QOpenGLFunctions>

#include "iostream"
namespace s21 {
struct FaceVertex {
  GLint v_index, t_index, n_index;
  friend std::ostream& operator<<(std::ostream& os, const FaceVertex& fv) {
    os << fv.v_index << " " << fv.t_index << " " << fv.n_index;
    return os;
  }
};
}  // namespace s21
#endif  // FACEVERTEX_H
