#include "Delegates/CChoicePathDelegate/CChoicePathDelegate.h"
CChoicePathDelegate::CChoicePathDelegate(QObject *parent)
    : QItemDelegate(parent) {}

QWidget *CChoicePathDelegate::createEditor(QWidget *parent,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex &index) const {
  LineEdit *dlg = new LineEdit(index, parent);
  return dlg;
}

void CChoicePathDelegate::setEditorData(QWidget *editor,
                                        const QModelIndex &index) const {
  //в этой функции на входе данные из модели и указатель на виджет редактора
  QString value = index.model()->data(index).toString();
  LineEdit *fileDialog = static_cast<LineEdit *>(editor);
  fileDialog->setText(value);  //устанавливаем текст
}

void CChoicePathDelegate::setModelData(QWidget *editor,
                                       QAbstractItemModel *model,
                                       const QModelIndex &index) const {
  //сюда попадаем когда редактор делегата теряем фокус/закрывается
  LineEdit *fileDialog = static_cast<LineEdit *>(editor);
  if (!fileDialog->getChoice().isEmpty())
    model->setData(index, fileDialog->getChoice());
}
