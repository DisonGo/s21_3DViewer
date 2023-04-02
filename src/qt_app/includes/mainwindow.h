#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractButton>
#include <QVector3D>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QVector3D translation = QVector3D(0,0,0);
    QVector3D rotation = QVector3D(0,0,0);
    Ui::MainWindow *ui;
private slots:
    void choose_file();
    void choose_color();
    void on_pushButton_loadFile_clicked();
    void on_doubleSpinBox_widthLine_valueChanged(double arg1);
    void on_doubleSpinBox_widthTop_valueChanged(double arg1);
    void updateCircleType(QAbstractButton *but);
    void updateZPlane(double value);
    void on_doubleSpinBox_scale_valueChanged(double arg1);
    void on_doubleSpinBox_moveX_valueChanged(double arg1);
    void on_doubleSpinBox_moveY_valueChanged(double arg1);
    void on_doubleSpinBox_moveZ_valueChanged(double arg1);
    void on_doubleSpinBox_rotateX_valueChanged(double arg1);
    void on_doubleSpinBox_rotateY_valueChanged(double arg1);
    void on_doubleSpinBox_rotateZ_valueChanged(double arg1);
    void setCameraMode(QAbstractButton *but);
    void setLinePattern(QAbstractButton *but);
    void updateInfoLabels(long vertN, long edgesN, QString filename);
};
#endif // MAINWINDOW_H
