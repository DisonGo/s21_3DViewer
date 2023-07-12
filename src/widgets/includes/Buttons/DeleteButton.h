#ifndef DELETEBUTTON_H
#define DELETEBUTTON_H
#include <QModelIndex>
#include <QPushButton>
class DeleteButton : public QPushButton {
 Q_OBJECT
 public:
  DeleteButton(const QModelIndex& index, QWidget* parent = nullptr)
      : QPushButton(parent), index_(index) {
    connect(this, &DeleteButton::clicked, this,
            &DeleteButton::TrigerClickedIndex);
    setText("X");
  };
 signals:
  void ClickedIndex(const QModelIndex&);

 private:
  QModelIndex index_;
 private slots:
  void TrigerClickedIndex() { emit ClickedIndex(index_); };
};

#endif  // DELETEBUTTON_H
