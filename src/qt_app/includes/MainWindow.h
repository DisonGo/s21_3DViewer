#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <FileImportWidget.h>
#include <OGLWidget.h>
#include <godison/Vectors.h>

#include <QAbstractButton>
#include <QMainWindow>
#include <QSettings>
#include <QSplitter>
#include <QTreeView>

#include "ConfigWidgetFactory.h"
#include "Spacers/DrawConfigSpacer.h"
#include "Spacers/EngineSpacer.h"
using godison::vectors::Vector3D;
namespace Ui {
class MainWindow;
}
namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(EngineSpacer& engine_spacer, DrawConfigSpacer& draw_config_spacer,
             QWidget* parent = nullptr);
  ~MainWindow();

 private:
  QSettings settings_;
  QSplitter* splitter_ = nullptr;
  QTreeView* object_tree = nullptr;
  ::Ui::MainWindow* ui;
  OGLWidget* openGLWidget = nullptr;
  EngineSpacer& engine_spacer_;
  DrawConfigSpacer& draw_config_spacer_;
  void saveSettings();
  void Setup();
  void SetupView();
 private slots:
  void ShowObjectWidget(s21::EObject* object);
  void SetupEObjectTreeView();
  void UpdateGL();

  void ImportFile(QString path);
  void ChooseBackColor();
  void loadSettings();
  void closeEvent(QCloseEvent* event) override;
};
}  // namespace s21
#endif  // MAINWINDOW_H
