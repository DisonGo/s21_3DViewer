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
  float GetPointSize() const { return config_->PointSize; };
  float GetLineWidth() const { return config_->LineWidth; };
  bool GetPoints() const { return config_->Points; };
  bool GetLines() const { return config_->Lines; };
  bool GetTriangles() const { return config_->Triangles; };
  bool GetTrianglesStrip() const { return config_->TrianglesStrip; };
  bool GetRoundCircle() const { return config_->RoundCircle; };
  bool GetDashedLines() const { return config_->DashedLines; };
  bool GetIndexDraw() const { return config_->IndexDraw; };
  bool GetVertexOnlyDraw() const { return config_->VertexOnlyDraw; };
  const QColor& GetFragmentColor() const { return config_->FragmentColor; };
  const QColor& GetLineColor() const { return config_->LineColor; };
  const QColor& GetDotColor() const { return config_->DotColor; };
  const QColor& GetBackColor() const { return config_->BackColor; };
 public slots:
  void SetPointSize(float newPointSize) { config_->PointSize = newPointSize; };
  void SetLineWidth(float newLineWidth) { config_->LineWidth = newLineWidth; };
  void SetPoints(int newPoints) { config_->Points = (bool)newPoints; };
  void SetLines(int newLines) { config_->Lines = (bool)newLines; };
  void SetTriangles(int newTriangles) {
    config_->Triangles = (bool)newTriangles;
  };
  void SetTrianglesStrip(int newTrianglesStrip) {
    config_->TrianglesStrip = (bool)newTrianglesStrip;
  };
  void SetRoundCircle(int newRoundCircle) {
    config_->RoundCircle = (bool)newRoundCircle;
  };
  void SetDashedLines(int newDashedLines) {
    config_->DashedLines = (bool)newDashedLines;
  };
  void SetIndexDraw(int newIndexDraw) { config_->IndexDraw = newIndexDraw; };
  void SetVertexOnlyDraw(int newVertexOnlyDraw) {
    config_->VertexOnlyDraw = newVertexOnlyDraw;
  };
  void SetFragmentColor(const QColor& newFragmentColor) {
    config_->FragmentColor = newFragmentColor;
  };
  void SetLineColor(const QColor& newLineColor) {
    config_->LineColor = newLineColor;
  };
  void SetDotColor(const QColor& newDotColor) {
    config_->DotColor = newDotColor;
  };
  void SetBackColor(const QColor& newBackColor) {
    config_->BackColor = newBackColor;
  };

 private:
  DrawConfig* config_;  // DrawConfig - Singltone
};
#endif  // DRAWCONFIGSPACER_H
