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
  float PointSize = 1;
  float LineWidth = 1;
  bool Points = true;
  bool Lines = true;
  bool Triangles = true;
  bool TrianglesStrip = false;
  bool RoundCircle = false;
  bool DashedLines = false;
  bool IndexDraw = false;
  bool VertexOnlyDraw = true;
  QColor FragmentColor = QColor(255, 255, 255);
  QColor LineColor = QColor(255, 255, 255);
  QColor DotColor = QColor(255, 255, 255);
  QColor BackColor = QColor(0, 0, 0);

 private:
  DrawConfig(){};
  DrawConfig(const DrawConfig&);
  const DrawConfig& operator=(const DrawConfig&);
  ~DrawConfig(){};
};
#endif  // DRAWCONFIG_H
