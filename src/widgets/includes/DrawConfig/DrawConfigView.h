#ifndef DRAWCONFIGVIEW_H
#define DRAWCONFIGVIEW_H

#include <QWidget>

#include "Spacers/DrawConfigSpacer.h"
#include "DrawConfig.h"
namespace Ui {
class DrawConfigView;
}

class DrawConfigView : public QWidget {
  Q_OBJECT

 public:
  explicit DrawConfigView(QWidget *parent = nullptr);
  ~DrawConfigView();
 signals:
  void DrawConfigUpdated();

 private:
  DrawConfigSpacer drawConfigSpacer_;
  Ui::DrawConfigView *ui;
};

#endif  // DRAWCONFIGVIEW_H
