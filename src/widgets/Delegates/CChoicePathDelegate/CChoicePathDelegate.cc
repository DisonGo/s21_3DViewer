#include "Delegates/CChoicePathDelegate/CChoicePathDelegate.h"
#include <QPushButton>
ComboBoxDelegate::ComboBoxDelegate(QObject *parent)
    : QStyledItemDelegate(parent) {}

QWidget *ComboBoxDelegate::createEditor(
    QWidget *parent, const QStyleOptionViewItem & /* option */,
    const QModelIndex &index) const {
  QLineEdit *editor = new QLineEdit(parent);
  editor->setText(index.data(Qt::DisplayRole).toString());
  return editor;
}

void ComboBoxDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const {
  QString value = index.model()->data(index, Qt::EditRole).toString();
  QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);
  lineEdit->setText(value);
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const {
  QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);
  QString value = lineEdit->text();
  model->setData(index, value, Qt::EditRole);
}

//void ComboBoxDelegate::paint(QPainter *painter,
//                             const QStyleOptionViewItem &option,
//                             const QModelIndex &index) const {
//  QPaintDevice *original_pdev_ptr = painter->device();
//  if (option.state & QStyle::State_Selected)
//    painter->fillRect(option.rect, option.palette.highlight());
//  QPushButton item_widget;
//  item_widget.setText(index.data(Qt::DisplayRole).toString());
//  auto pal = item_widget.palette();
//  pal.setColor(item_widget.foregroundRole(), {255,255,255});
//  item_widget.setPalette(pal);
//  item_widget.setGeometry(option.rect);
//  painter->end();
//  item_widget.render(painter->device(),
//                     QPoint(option.rect.x(), option.rect.y()),
//                     QRegion(0, 0, option.rect.width(), option.rect.height()),
//                     QWidget::RenderFlag::DrawChildren);
//  painter->begin(original_pdev_ptr);
//  painter->drawEllipse(0, 0, 10, 10);
//}
