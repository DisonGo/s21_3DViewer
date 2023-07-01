#ifndef STYLELOADER_H
#define STYLELOADER_H
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QFileSystemWatcher>
#include <QKeyEvent>
#include <QKeySequence>
#include <QObject>
class StyleLoader : public QObject {
  Q_OBJECT
 public:
  StyleLoader(QObject* parent, const QString& filename);
  void attach(void);
  static QString defaultStyleFile();

 private:
  QString m_filename;
  QFileSystemWatcher watcher;
 private slots:
  void setAppStyleSheet();
};

#endif  // STYLELOADER_H
