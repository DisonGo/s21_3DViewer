#ifndef CONFIGWIDGET_H
#define CONFIGWIDGET_H
#include <QWidget>
namespace s21 {
class ConfigWidget : public QWidget {
  Q_OBJECT
 public:
  using QWidget::QWidget;
 signals:
  void UpdateRequest();
};
}
#endif  // CONFIGWIDGET_H
