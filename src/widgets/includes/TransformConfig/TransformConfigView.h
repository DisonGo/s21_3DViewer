#ifndef TRANSFORMWIDGET_H
#define TRANSFORMWIDGET_H

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
  ~TransformConfigView();

 public slots:
  void ResetValues();
 signals:
  void TransformUpdated();
 private slots:
  void SetTranformSpacer(TransformSpacer* transform);
  void SetTranslation(const QVector3D);
  void SetRotation(const QVector3D);
  void SetScale(const QVector3D);

 private:
  TransformSpacer* transformSpacer_ = nullptr;
  Ui::TransformConfigView* ui;
};

#endif  // TRANSFORMWIDGET_H
