#ifndef VERTEX_H
#define VERTEX_H
#include <QOpenGLFunctions>

#include "iostream"
namespace s21 {
struct Vertex {
  GLfloat x, y, z;
  Vertex(){};
  Vertex(float X, float Y, float Z) : x(X), y(Y), z(Z){};
  friend std::ostream& operator<<(std::ostream& os, const Vertex& v) {
    os << v.x << " " << v.y << " " << v.z;
    return os;
  }
};
}  // namespace s21

#endif  // VERTEX_H
