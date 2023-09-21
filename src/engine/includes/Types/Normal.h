#ifndef NORMAL_H
#define NORMAL_H
#include <QOpenGLFunctions>

#include "iostream"
namespace s21 {
struct Normal {
  GLfloat x, y, z;
  friend std::ostream& operator<<(std::ostream& os, const Normal& n) {
    os << n.x << " " << n.y << " " << n.z;
    return os;
  }
};
}  // namespace s21
#endif  // NORMAL_H
