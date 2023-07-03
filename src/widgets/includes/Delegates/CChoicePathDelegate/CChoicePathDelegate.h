#ifndef CCHOICEPATHDELEGATE_H
#define CCHOICEPATHDELEGATE_H
#include <QItemDelegate>
#include <QLineEdit>
#include <QToolButton>

class LineEdit : public QLineEdit {
  Q_OBJECT

 public:
  LineEdit(const QModelIndex &index, QWidget *parent = nullptr) : QLineEdit(parent) {};
  ~LineEdit() {};
  QString getChoice() { return fileName; }

 protected:
  void resizeEvent(QResizeEvent *){};  //в этой функции делаем так чтобы текст не
                                     //залезал под кнопку

 private slots:
  void pressButton(){};  //здесь вызов диалога выбора файла/каталога

 private:
  QToolButton *clearButton;
  QModelIndex indexSource;
  QString fileName;
};
class CChoicePathDelegate : public QItemDelegate {
 public:
  CChoicePathDelegate(QObject *parent = 0);
  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                        const QModelIndex &index)
      const;
  void setEditorData(QWidget *editor, const QModelIndex &index)
      const;
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index)
      const;
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                            const QModelIndex &index) const {};
};
#endif  // CCHOICEPATHDELEGATE_H
