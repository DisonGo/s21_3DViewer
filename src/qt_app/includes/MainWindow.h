#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <godison/Vectors.h>
using godison::vectors::Vector3D;
#include <QAbstractButton>
#include <QMainWindow>
#include <QSettings>
#include "ConfigWidgetFactory.h"
#include "E/Camera.h"
#include "Engine.h"
#include <FileImportWidget.h>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  std::vector<QString> filePaths;
  Ui::MainWindow *ui;
  std::vector<QImage> gifBuffer;
  bool timerStarted = false;
  s21::EObjectItemModel *eObjectModel;

  void saveSettings();
  void saveGif(std::vector<QImage> gifData);
 private slots:
  void ShowObjectWidget(s21::EObject *object);
  void SetupEObjectTreeView();
  void UpdateGL();

  void ImportFile(QString path);

  void loadSettings();
  void applySettings();
  void closeEvent(QCloseEvent *event) override;
  void on_pushButton_saveFile_clicked();
  void on_pushButton_screencast_clicked();
  void on_pushButton_screencast_auto_clicked();
  void endCapture();
};
#endif  // MAINWINDOW_H
