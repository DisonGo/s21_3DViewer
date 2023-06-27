#include "StyleLoader.h"

void StyleLoader::attach(void) { watcher.addPath(m_filename); }
void StyleLoader::setAppStyleSheet() {
  QFile file(m_filename);
  if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << "Cannot open stylesheet file " << m_filename;
    return;
  }
  QString stylesheet = QString::fromUtf8(file.readAll());
  qApp->setStyleSheet(stylesheet);
}

QString StyleLoader::defaultStyleFile() { return ":/style.qss"; }

StyleLoader::StyleLoader(QObject* parent, const QString& filename)
    : QObject(parent), m_filename(filename) {
  QObject::connect(&watcher, SIGNAL(fileChanged(QString)), this,
                   SLOT(setAppStyleSheet()));
  setAppStyleSheet();
}
