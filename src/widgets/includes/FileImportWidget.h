#ifndef FILEIMPORTWIDGET_H
#define FILEIMPORTWIDGET_H

#include <QWidget>

namespace Ui {
class FileImportWidget;
}
namespace s21 {
class FileImportWidget : public QWidget
{
  Q_OBJECT
public:
  explicit FileImportWidget(QWidget *parent = nullptr);
  ~FileImportWidget();
  void ImportPaths(QVector<QString> paths);
  void ImportPaths(std::vector<QString> paths);
  void ImportPaths(std::vector<std::string> paths);

  std::vector<std::string> ExportPaths();
  QVector<QString> ExportPathsQ();
signals:
  void FileImporting(QString path);

private slots:
  void ChooseFile();
  void ImportFile();
private:
  std::vector<std::string> PathsToStdVector();
  void Setup();
  QVector<QString> file_paths_;
  ::Ui::FileImportWidget *ui;
};
}
#endif // FILEIMPORTWIDGET_H
