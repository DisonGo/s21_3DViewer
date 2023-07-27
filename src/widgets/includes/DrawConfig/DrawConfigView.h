#ifndef DRAWCONFIGVIEW_H
#define DRAWCONFIGVIEW_H

#include "ConfigWidget.h"
#include "DrawConfig.h"
#include "Spacers/DrawConfigSpacer.h"
namespace Ui {
class DrawConfigView;
}

class DrawConfigView : public ConfigWidget {
  Q_OBJECT

 public:
  explicit DrawConfigView(s21::DrawConfig& draw_config, QWidget *parent = nullptr);
  ~DrawConfigView();
 signals:
  void DrawConfigUpdated();

 private:
  s21::DrawConfigSpacer drawConfigSpacer_;
  Ui::DrawConfigView *ui;
};

#endif  // DRAWCONFIGVIEW_H
