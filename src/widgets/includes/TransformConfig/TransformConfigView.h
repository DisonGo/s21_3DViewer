#ifndef TRANSFORMCONFIGVIEW_H
#define TRANSFORMCONFIGVIEW_H

#include <QVector3D>
#include <QWidget>

#include "Spacers/TransformSpacer.h"
namespace Ui {
class TransformConfigView;
}

class TransformConfigView : public QWidget {
  Q_OBJECT

 public:
  explicit TransformConfigView(QWidget* parent = nullptr);
  explicit TransformConfigView(s21::TransformSpacer* transform,
                               QWidget* parent = nullptr);
  ~TransformConfigView();

 public slots:
  void ResetValues();
  void SetValuesFromConfig();
  void SetTranformSpacer(s21::TransformSpacer* transform);
  void SetTranslation(const QVector3D);
  void SetRotation(const QVector3D);
  void SetScale(const QVector3D);
 signals:
  void UpdateRequest();
  void TransformUpdated();

 private:
  void Setup();
  s21::TransformSpacer* transformSpacer_ = nullptr;
  Ui::TransformConfigView* ui;
};
#endif  // TRANSFORMCONFIGVIEW_H
