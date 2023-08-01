#include "StyleLoader.h"
namespace s21 {
void StyleLoader::Attach(void) { watcher_.addPath(filename_); }
void StyleLoader::SetAppStyleSheet() {
  QFile file(filename_);
  if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << "Cannot open stylesheet file " << filename_;
    return;
  }
  QString stylesheet = QString::fromUtf8(file.readAll());
  qApp->setStyleSheet(stylesheet);
}

QString StyleLoader::DefaultStyleFile() { return ":/style.qss"; }

StyleLoader::StyleLoader(QObject* parent, const QString& filename)
    : QObject(parent), filename_(filename) {
  QObject::connect(&watcher_, SIGNAL(fileChanged(QString)), this,
                   SLOT(SetAppStyleSheet()));
  SetAppStyleSheet();
}
}  // namespace s21
