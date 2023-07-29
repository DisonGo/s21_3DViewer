#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <FileImportWidget.h>
#include <ImageSaverControler.h>
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
             ImageSaverControler& image_saver_controler,
             QWidget* parent = nullptr);
  ~MainWindow();

 private:
  unsigned gif_fps_ = 10;
  unsigned gif_length_ = 5;
  QSize gif_resolution_ = QSize(640, 480);
  QSettings settings_;
  QSplitter* splitter_ = nullptr;
  QTreeView* object_tree_ = nullptr;
  ::Ui::MainWindow* ui;
  OGLWidget* openGLWidget = nullptr;
  EngineSpacer& engine_spacer_;
  DrawConfigSpacer& draw_config_spacer_;
  ImageSaverControler& image_saver_controler_;
  void Setup();
  void SetupView();
  void SaveSettings();
  void LoadSettings();
 private slots:
  void ShowObjectWidget(s21::EObject* object);
  void StartRecord();
  void StopRecord();
  void SaveScreenshot();
  void SetupEObjectTreeView();
  void PrintImported(unsigned long vertices_n, unsigned long indices_n,
                     std::string file_name);
  void UpdateGL();

  void ImportFile(QString path);
  void ChooseBackColor();
  void closeEvent(QCloseEvent* event) override;
};
}  // namespace s21
#endif  // MAINWINDOW_H
