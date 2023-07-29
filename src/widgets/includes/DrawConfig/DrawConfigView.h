#ifndef DRAWCONFIGVIEW_H
#define DRAWCONFIGVIEW_H

#include "ConfigWidget.h"
#include "DrawConfig.h"
#include "Spacers/DrawConfigSpacer.h"
namespace Ui {
class DrawConfigView;
}
namespace s21 {
class DrawConfigView : public ConfigWidget {
  Q_OBJECT

 public:
  explicit DrawConfigView(s21::DrawConfig &draw_config,
                          QWidget *parent = nullptr);
  ~DrawConfigView();
 signals:
  void DrawConfigUpdated();

 private:
  s21::DrawConfigSpacer draw_config_spacer_;
  ::Ui::DrawConfigView *ui;
};
}  // namespace s21
#endif  // DRAWCONFIGVIEW_H
