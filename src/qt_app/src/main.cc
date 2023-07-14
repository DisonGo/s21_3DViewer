#include <StyleLoader.h>

#include <QApplication>
#include <QSurfaceFormat>

#include "MainWindow.h"
#include "Engine.h"
#include "DrawConfig.h"

int main(int argc, char *argv[]) {
  QSurfaceFormat format;
  s21::DrawConfig::Instance();
  format.setDepthBufferSize(24);
  format.setStencilBufferSize(8);
  format.setVersion(4, 1);
  format.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(format);
  QApplication a(argc, argv);
  const QString style_file_path = ":/style/style.qss";
  // const QString style_file_path =
  //     "/Users/evverenn/Desktop/Projects/Junk/3D_Viewer_v2/src/qt_app/resources/"
  //     "style/style.qss";
  MainWindow w;

  StyleLoader *style_loader = new StyleLoader(&w, style_file_path);
  style_loader->attach();
  w.show();
  return a.exec();
}
