#ifndef TEXTURECOORD_H
#define TEXTURECOORD_H
#include <QOpenGLFunctions>

#include "iostream"
namespace s21 {
struct TextureCoord {
  GLfloat u, v;
  friend std::ostream& operator<<(std::ostream& os, const TextureCoord& t) {
    os << t.u << " " << t.v;
    return os;
  }
};
}  // namespace s21
#endif  // TEXTURECOORD_H
