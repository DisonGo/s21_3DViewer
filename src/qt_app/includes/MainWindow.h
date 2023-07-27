#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <godison/Vectors.h>
using godison::vectors::Vector3D;
#include <FileImportWidget.h>
#include <OpenGLController.h>
#include <QAbstractButton>
#include <QMainWindow>
#include <QSettings>
#include <QTreeView>
#include "ConfigWidgetFactory.h"
#include "E/Camera.h"
#include <QSplitter>
#include "Engine.h"
#include "Spacers/EngineSpacer.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(s21::EngineSpacer& engine_spacer, QWidget *parent = nullptr);
  ~MainWindow();

 private:
  std::vector<QString> filePaths;
  Ui::MainWindow *ui;
  QSplitter* splitter_ = nullptr;
  OpenGLController* openGLWidget = nullptr;
  QTreeView* object_tree = nullptr;
  s21::EngineSpacer& engine_spacer_;
  void saveSettings();
 private slots:
  void ShowObjectWidget(s21::EObject *object);
  void SetupEObjectTreeView();
  void UpdateGL();

  void ImportFile(QString path);

  void loadSettings();
  void applySettings();
  void closeEvent(QCloseEvent *event) override;
};
#endif  // MAINWINDOW_H
