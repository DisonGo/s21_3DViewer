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
  float GetPointSize() const { return config_->point_size_; };
  float GetLineWidth() const { return config_->line_width_; };
  bool GetPoints() const { return config_->points_; };
  bool GetLines() const { return config_->lines_; };
  bool GetTriangles() const { return config_->triangles_; };
  bool GetTrianglesStrip() const { return config_->triangles_strip_; };
  bool GetRoundCircle() const { return config_->round_circle_; };
  bool GetDashedLines() const { return config_->dashed_lines_; };
  bool GetIndexDraw() const { return config_->index_draw_; };
  bool GetVertexOnlyDraw() const { return config_->vertex_only_draw_; };
  const QColor& GetFragmentColor() const { return config_->fragment_color_; };
  const QColor& GetLineColor() const { return config_->line_color_; };
  const QColor& GetDotColor() const { return config_->dot_color_; };
  const QColor& GetBackColor() const { return config_->back_color_; };
 public slots:
  void SetPointSize(float newPointSize) { config_->point_size_ = newPointSize; };
  void SetLineWidth(float newLineWidth) {
    config_->line_width_ = newLineWidth;
  };
  void SetPoints(int newPoints) { config_->points_ = (bool)newPoints; };
  void SetLines(int newLines) { config_->lines_ = (bool)newLines; };
  void SetTriangles(int newTriangles) {
    config_->triangles_ = (bool)newTriangles;
  };
  void SetTrianglesStrip(int newTrianglesStrip) {
    config_->triangles_strip_ = (bool)newTrianglesStrip;
  };
  void SetRoundCircle(int newRoundCircle) {
    config_->round_circle_ = (bool)newRoundCircle;
  };
  void SetDashedLines(int newDashedLines) {
    config_->dashed_lines_ = (bool)newDashedLines;
  };
  void SetIndexDraw(int newIndexDraw) { config_->index_draw_ = newIndexDraw; };
  void SetVertexOnlyDraw(int newVertexOnlyDraw) {
    config_->vertex_only_draw_ = newVertexOnlyDraw;
  };
  void SetFragmentColor(const QColor& newFragmentColor) {
    config_->fragment_color_ = newFragmentColor;
  };
  void SetLineColor(const QColor& newLineColor) {
    config_->line_color_ = newLineColor;
  };
  void SetDotColor(const QColor& newDotColor) {
    config_->dot_color_ = newDotColor;
  };
  void SetBackColor(const QColor& newBackColor) {
    config_->back_color_ = newBackColor;
  };

 private:
  DrawConfig* config_;  // DrawConfig - Singltone
};
#endif  // DRAWCONFIGSPACER_H
