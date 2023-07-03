#ifndef DRAWCONFIGSPACER_H
#define DRAWCONFIGSPACER_H
#include <QDebug>
#include <QObject>

#include "DrawConfig.h"
class DrawConfigSpacer : public QObject {
  Q_OBJECT
 public:
  DrawConfigSpacer(QObject* parent = nullptr) : QObject(parent) {
    config_ = &DrawConfig::Instance();
  };
  float GetPointSize() const { return config_->point_size; };
  float GetLineWidth() const { return config_->line_width; };
  bool GetPoints() const { return config_->points; };
  bool GetLines() const { return config_->lines; };
  bool GetTriangles() const { return config_->triangles; };
  bool GetTrianglesStrip() const { return config_->triangles_strip; };
  bool GetRoundCircle() const { return config_->round_circle; };
  bool GetDashedLines() const { return config_->dashed_lines; };
  bool GetIndexDraw() const { return config_->index_draw; };
  bool GetVertexOnlyDraw() const { return config_->vertex_only_draw; };
  const QColor& GetFragmentColor() const { return config_->fragment_color; };
  const QColor& GetLineColor() const { return config_->line_color; };
  const QColor& GetDotColor() const { return config_->dot_color; };
  const QColor& GetBackColor() const { return config_->back_color; };
 public slots:
  void SetPointSize(float newPointSize) {
    config_->point_size = newPointSize;
  };
  void SetLineWidth(float newLineWidth) { config_->line_width = newLineWidth; };
  void SetPoints(int newPoints) { config_->points = (bool)newPoints; };
  void SetLines(int newLines) { config_->lines = (bool)newLines; };
  void SetTriangles(int newTriangles) {
    config_->triangles = (bool)newTriangles;
  };
  void SetTrianglesStrip(int newTrianglesStrip) {
    config_->triangles_strip = (bool)newTrianglesStrip;
  };
  void SetRoundCircle(int newRoundCircle) {
    config_->round_circle = (bool)newRoundCircle;
  };
  void SetDashedLines(int newDashedLines) {
    config_->dashed_lines = (bool)newDashedLines;
  };
  void SetIndexDraw(int newIndexDraw) { config_->index_draw = newIndexDraw; };
  void SetVertexOnlyDraw(int newVertexOnlyDraw) {
    config_->vertex_only_draw = newVertexOnlyDraw;
  };
  void SetFragmentColor(const QColor& newFragmentColor) {
    config_->fragment_color = newFragmentColor;
  };
  void SetLineColor(const QColor& newLineColor) {
    config_->line_color = newLineColor;
  };
  void SetDotColor(const QColor& newDotColor) {
    config_->dot_color = newDotColor;
  };
  void SetBackColor(const QColor& newBackColor) {
    config_->back_color = newBackColor;
  };

 private:
  DrawConfig* config_;  // DrawConfig - Singltone
};
#endif  // DRAWCONFIGSPACER_H
