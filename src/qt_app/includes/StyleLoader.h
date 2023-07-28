#ifndef STYLELOADER_H
#define STYLELOADER_H
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QFileSystemWatcher>
#include <QKeyEvent>
#include <QKeySequence>
#include <QObject>
namespace s21 {
class StyleLoader : public QObject {
  Q_OBJECT
 public:
  StyleLoader(QObject* parent, const QString& filename);
  void Attach(void);
  static QString DefaultStyleFile();

 private:
  QString filename_;
  QFileSystemWatcher watcher_;
 private slots:
  void SetAppStyleSheet();
};
}  // namespace s21
#endif  // STYLELOADER_H
