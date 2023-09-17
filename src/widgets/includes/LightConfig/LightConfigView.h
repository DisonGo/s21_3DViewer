#ifndef LIGHTCONFIGVIEW_H
#define LIGHTCONFIGVIEW_H

#include "ConfigWidget.h"
#include "Spacers/LightSpacer.h"
namespace Ui {
class LightConfigView;
}

namespace s21 {
class LightConfigView : public ConfigWidget {
  Q_OBJECT
 public:
  explicit LightConfigView(QWidget* parent = nullptr);
  explicit LightConfigView(s21::LightSpacer* light_spacer,
                           QWidget* parent = nullptr);
  ~LightConfigView();
 public slots:
  void SetLightSpacer(s21::LightSpacer* light_spacer);
  void SetValuesFromConfig();

  void SetPosition(const godison::vectors::Vector3D& new_position);
  void SetColor(const godison::vectors::Vector3D& new_color);
  void SetStrength(float new_strength);

 private:
  using Vector3D = godison::vectors::Vector3D;
  void Setup();
  s21::LightSpacer* light_spacer_ = nullptr;
  ::Ui::LightConfigView* ui;
};

}  // namespace s21
#endif  // LIGHTCONFIGVIEW_H
