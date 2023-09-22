#ifndef DRAWCONFIGSPACER_H
#define DRAWCONFIGSPACER_H
#include <QDebug>
#include <QObject>

#include "DrawConfig.h"
namespace s21 {
class DrawConfigSpacer : public QObject {
  Q_OBJECT
 public:
  DrawConfigSpacer(DrawConfig& config, QObject* parent = nullptr);
  bool GetPoints() const { return config_.points; };
  bool GetLines() const { return config_.lines; };
  bool GetTriangles() const { return config_.triangles; };
  bool GetTrianglesStrip() const { return config_.triangles_strip; };

  const godison::vectors::Vector3D& GetBackColor() const {
    return config_.back_color;
  };
 public slots:

  void SetPoints(int newPoints) { config_.points = (bool)newPoints; };
  void SetLines(int newLines) { config_.lines = (bool)newLines; };
  void SetTriangles(int newTriangles) {
    config_.triangles = (bool)newTriangles;
  };
  void SetTrianglesStrip(int newTrianglesStrip) {
    config_.triangles_strip = (bool)newTrianglesStrip;
  };
  void SetBackColor(const godison::vectors::Vector3D& newBackColor) {
    config_.back_color = newBackColor;
  };

 private:
  DrawConfig& config_;
};
}  // namespace s21
#endif  // DRAWCONFIGSPACER_H
