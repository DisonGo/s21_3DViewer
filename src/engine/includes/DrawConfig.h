#ifndef DRAWCONFIG_H
#define DRAWCONFIG_H
#include <QColor>
#include <QDebug>
namespace s21 {
class DrawConfig {
 public:
  static DrawConfig& Instance() {
    static DrawConfig instance;
    return instance;
  }
  float point_size = 1;
  float line_width = 1;
  bool points = true;
  bool lines = false;
  bool triangles = true;
  bool triangles_strip = false;
  bool round_circle = false;
  bool dashed_lines = false;
  QColor fragment_color = QColor(255, 255, 255);
  QColor line_color = QColor(255, 255, 255);
  QColor dot_color = QColor(255, 255, 255);
  QColor back_color = QColor(0, 0, 0);

 private:
  DrawConfig() = default;
  DrawConfig(const DrawConfig& old) = delete;
  const DrawConfig& operator=(const DrawConfig& old) = delete;
  ~DrawConfig() = default;
};
}  // namespace s21
#endif  // DRAWCONFIG_H
