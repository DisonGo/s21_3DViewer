#include <ImageSaverControler.h>
#include <StyleLoader.h>

#include <QApplication>
#include <QSurfaceFormat>

#include "DrawConfig.h"
#include "Engine.h"
#include "MainWindow.h"
#include "Spacers/DrawConfigSpacer.h"
#include "Spacers/EngineSpacer.h"
#include "iostream"
int main(int argc, char *argv[]) {
  QCoreApplication::setOrganizationName("godison_co");
  QCoreApplication::setApplicationName("3D Viewer 2.0");

  s21::Logger::DeactivateLogLevel(s21::Logger::LogLevel::kBasic);

  QSurfaceFormat format;
  format.setDepthBufferSize(16);
  format.setStencilBufferSize(4);
  format.setSwapBehavior(QSurfaceFormat::TripleBuffer);
  format.setSamples(4);
  format.setVersion(4, 1);
  format.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(format);

  QApplication a(argc, argv);

  s21::ImageSaver image_saver;
  s21::ImageSaverControler saver_controler(image_saver);

  s21::DrawConfig config;
  // config.lines = false;
  // config.triangles = false;
  s21::DrawConfigSpacer config_spacer(config);

  s21::Engine engine(config);
  s21::EngineSpacer engine_spacer(engine);
  s21::MainWindow w(engine_spacer, config_spacer, saver_controler);
  const QString style_file_path = ":/style/style.qss";
  auto *style_loader = new s21::StyleLoader(&w, style_file_path);
  style_loader->Attach();
  w.show();
  return a.exec();
}
