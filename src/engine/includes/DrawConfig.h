#ifndef DRAWCONFIG_H
#define DRAWCONFIG_H
#include <QColor>
#include <QDebug>
class DrawConfig {
 public:
  static DrawConfig& Instance() {
    static DrawConfig instance_;
    return instance_;
  };
  float point_size_ = 1;
  float line_width_ = 1;
  bool points_ = true;
  bool lines_ = true;
  bool triangles_ = true;
  bool triangles_strip_ = false;
  bool round_circle_ = false;
  bool dashed_lines_ = false;
  bool index_draw_ = false;
  bool vertex_only_draw_ = true;
  QColor fragment_color_ = QColor(255, 255, 255);
  QColor line_color_ = QColor(255, 255, 255);
  QColor dot_color_ = QColor(255, 255, 255);
  QColor back_color_ = QColor(0, 0, 0);

 private:
  DrawConfig(){};
  DrawConfig(const DrawConfig&);
  const DrawConfig& operator=(const DrawConfig&);
  ~DrawConfig(){};
};
#endif  // DRAWCONFIG_H
