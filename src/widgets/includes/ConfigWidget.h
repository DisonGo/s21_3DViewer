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
}  // namespace s21
#endif  // CONFIGWIDGET_H
