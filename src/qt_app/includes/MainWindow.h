#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <godison/Vectors.h>
#include <QAbstractButton>
#include <QMainWindow>
#include <QSettings>
#include <QTreeView>
#include <QSplitter>
#include <FileImportWidget.h>
#include <OpenGLController.h>
#include "ConfigWidgetFactory.h"
#include "Spacers/EngineSpacer.h"
using godison::vectors::Vector3D;
namespace Ui {
class MainWindow;
}
namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(EngineSpacer& engine_spacer, QWidget *parent = nullptr);
  ~MainWindow();

 private:
  QSplitter* splitter_ = nullptr;
  QTreeView* object_tree = nullptr;
  ::Ui::MainWindow *ui;
  OpenGLController* openGLWidget = nullptr;
  EngineSpacer& engine_spacer_;
  std::vector<QString> filePaths;
  void saveSettings();
  void Setup();
  void SetupView();
 private slots:
  void ShowObjectWidget(s21::EObject *object);
  void SetupEObjectTreeView();
  void UpdateGL();

  void ImportFile(QString path);

  void loadSettings();
  void applySettings();
  void closeEvent(QCloseEvent *event) override;
};
}
#endif  // MAINWINDOW_H
