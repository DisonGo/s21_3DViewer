#ifndef DRAWCONFIG_H
#define DRAWCONFIG_H
#include <QColor>
#include <QDebug>
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
  bool triangles = false;
  bool triangles_strip = false;
  QColor back_color = QColor(1, 10, 27);
};
}  // namespace s21
#endif  // DRAWCONFIG_H
