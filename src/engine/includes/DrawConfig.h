#ifndef DRAWCONFIG_H
#define DRAWCONFIG_H
#include <QColor>
#include <QDebug>
namespace s21 {
class DrawConfig {
 public:
  static DrawConfig& Instance();
  bool points = true;
  bool lines = true;
  bool triangles = false;
  bool triangles_strip = false;
  QColor back_color = QColor(1, 10, 27);

 private:
  DrawConfig() = default;
  DrawConfig(const DrawConfig& old) = delete;
  const DrawConfig& operator=(const DrawConfig& old) = delete;
  ~DrawConfig() = default;
};
}  // namespace s21
#endif  // DRAWCONFIG_H
