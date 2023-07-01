#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <CameraConfig/CameraConfigView.h>
#include <TransformConfig/TransformConfigView.h>

#include <QAbstractButton>
#include <QMainWindow>
#include <QSettings>
#include <QVector3D>

#include "E/Camera.h"
#include "Engine.h"
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
  QColor lineColor = QColor(255, 255, 255);
  QColor pointColor = QColor(255, 0, 0);
  QColor backColor = QColor(0, 0, 0);

  float lineWidth = 1;
  float pointWidth = 1;
  int pointTypeIndex = -1;
  int viewTypeIndex = -1;
  int fileFieldIndex = -1;
  bool loading_setting_done = false;
  std::vector<QString> filePaths;
  float scale = 1;
  Ui::MainWindow *ui;
  std::vector<QImage> gifBuffer;
  bool timerStarted = false;
  EObjectItemModel *eObjectModel;
  QVector3D cameraPos = QVector3D(0, 0, 0);
  QVector3D cameraOrient = QVector3D(0, 0, 1);

  void saveSettings();
  void saveGif(std::vector<QImage> gifData);
 private slots:
  void ShowObjectWidget(EObject *object);
  void SetupEObjectTreeView();
  void UpdateGL();
  void TranslationTest(QVector3D values);
  void choose_file();

  void on_pushButton_loadFile_clicked();

  void updateInfoLabels(long vertN, long edgesN, QString filename);
  void loadSettings();
  void applySettings();
  void closeEvent(QCloseEvent *event) override;
  void on_comboBox_tab1_currentIndexChanged(int index);
  void on_pushButton_saveFile_clicked();
  void on_pushButton_screencast_clicked();
  void on_pushButton_screencast_auto_clicked();
  void endCapture();
};
#endif  // MAINWINDOW_H
