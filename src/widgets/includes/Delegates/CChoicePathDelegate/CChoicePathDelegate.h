#ifndef CCHOICEPATHDELEGATE_H
#define CCHOICEPATHDELEGATE_H
#include <QComboBox>
#include <QLineEdit>
#include <QStyledItemDelegate>
#include <QToolButton>
#include <QPainter>
class ComboBoxDelegate : public QStyledItemDelegate {
  Q_OBJECT

 public:
  ComboBoxDelegate(QObject *parent = 0);

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const;

  void setEditorData(QWidget *editor, const QModelIndex &index) const;
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const;

  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                            const QModelIndex &index) const {};
//  void paint(QPainter *painter, const QStyleOptionViewItem &option,
//             const QModelIndex &index) const;
};



#endif  // CCHOICEPATHDELEGATE_H
