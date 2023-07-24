#ifndef CONFIGWIDGET_H
#define CONFIGWIDGET_H
#include <QWidget>

class ConfigWidget : public QWidget {
  Q_OBJECT
 public:
  Q_PROPERTY(QString class)
  using QWidget::QWidget;
 signals:
  void UpdateRequest();
};

#endif  // CONFIGWIDGET_H
