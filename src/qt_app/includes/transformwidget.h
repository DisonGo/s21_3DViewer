#ifndef TRANSFORMWIDGET_H
#define TRANSFORMWIDGET_H

#include <QWidget>
#include <QVector3D>
#include "Types/Transform.h"
#include "Mesh.h"
namespace Ui {
class TransformWidget;
}

class TransformWidget : public QWidget
{
  Q_OBJECT

public:
  explicit TransformWidget(QWidget *parent = nullptr);
  ~TransformWidget();

  void LinkMesh(Mesh* mesh);
public slots:
  void ResetValues();
signals:
  void TransformUpdated();
private slots:
  void LinkTranform(Transform* transform);
  void SetTranslation(const QVector3D);
  void SetRotation(const QVector3D);
  void SetScale(const QVector3D);
private:
  Mesh* mesh = nullptr;
  Transform* transform = nullptr;
  Ui::TransformWidget *ui;
};

#endif // TRANSFORMWIDGET_H
