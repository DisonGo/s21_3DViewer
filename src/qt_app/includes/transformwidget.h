#ifndef TRANSFORMWIDGET_H
#define TRANSFORMWIDGET_H

#include <QWidget>
#include <QVector3D>
namespace Ui {
class TransformWidget;
}

class TransformWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TransformWidget(QWidget *parent = nullptr);
    ~TransformWidget();
public slots:
    void ResetValues();
signals:
    void TranslationChanged(const QVector3D);
    void RotationChanged(const QVector3D);
    void ScaleChanged(const QVector3D);
private:
    QVector3D translation = QVector3D(0,0,0);
    QVector3D rotation = QVector3D(0,0,0);
    QVector3D scale = QVector3D(0,0,0);
    Ui::TransformWidget *ui;
};

#endif // TRANSFORMWIDGET_H
