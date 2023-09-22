#ifndef DRAWCONFIG_H
#define DRAWCONFIG_H
#include "godison/Vectors.h"
namespace s21 {
class DrawConfig {
 public:
  DrawConfig() = default;
  DrawConfig(const DrawConfig& old);
  DrawConfig& operator=(const DrawConfig& old) = default;
  DrawConfig& operator=(DrawConfig&& old) = delete;
  ~DrawConfig() = default;
  bool points = true;
  bool lines = true;
  bool triangles = true;
  bool triangles_strip = false;
  godison::vectors::Vector3D back_color{1, 10, 27};
};
}  // namespace s21
#endif  // DRAWCONFIG_H
