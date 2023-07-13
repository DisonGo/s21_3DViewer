#ifndef CAMERACONFIGVIEW_H
#define CAMERACONFIGVIEW_H

#include <QAbstractButton>

#include "ConfigWidget.h"
#include "Spacers/CameraSpacer.h"

namespace Ui {
class CameraConfigView;
}

class CameraConfigView : public ConfigWidget {
  Q_OBJECT

 public:
  explicit CameraConfigView(s21::CameraSpacer* cameraSpacer, QWidget* parent = nullptr);
  ~CameraConfigView();
  s21::CameraSpacer *GetCameraSpacer();
  void SetCameraSpacer(s21::CameraSpacer* cameraSpacer);
 private slots:
  void SetValuesFromConfig();
  void SetPosition(const QVector3D&);
  void SetOrientation(const QVector3D&);
  void SetFocusPoint(const QVector3D&);
  void SetCameraMode(QAbstractButton*);
  void SetViewMode(QAbstractButton*);
  void SetFOV(int);
  void SetZNear(double);
  void SetZFar(double);
  void SetBoxLeft(double);
  void SetBoxRight(double);
  void SetBoxBottom(double);
  void SetBoxTop(double);

 private:
  void SetupConnects();
  s21::CameraSpacer* cameraSpacer_{};
  Ui::CameraConfigView* ui;
};

#endif  // CAMERACONFIGVIEW_H
