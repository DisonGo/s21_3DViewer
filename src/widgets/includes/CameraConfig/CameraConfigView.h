#ifndef CAMERACONFIGVIEW_H
#define CAMERACONFIGVIEW_H

#include <QAbstractButton>
#include <QWidget>

#include "Spacers/CameraSpacer.h"

namespace Ui {
class CameraConfigView;
}

class CameraConfigView : public QWidget {
  Q_OBJECT

 public:
  explicit CameraConfigView(QWidget* parent = nullptr,
                            CameraSpacer* cameraSpacer = nullptr);
  ~CameraConfigView();

  void SetCameraSpacer(CameraSpacer* cameraSpacer);
 signals:
  void UpdateRequest();
 private slots:
  //  void on_ResetBut_clicked();
  void SetValuesFromConfig();
  void SetPosition(const QVector3D&);
  void SetOrientation(const QVector3D&);
  void SetFocusPoint(const QVector3D&);
  void SetCameraMode(QAbstractButton*);
  void SetViewMode(QAbstractButton*);
  void SetZNear(double);
  void SetZFar(double);
  void SetBoxLeft(double);
  void SetBoxRight(double);
  void SetBoxBottom(double);
  void SetBoxTop(double);

 private:
  void SetupConnects();
  CameraSpacer* cameraSpacer_{};
  Ui::CameraConfigView* ui;
};

#endif  // CAMERACONFIGVIEW_H
