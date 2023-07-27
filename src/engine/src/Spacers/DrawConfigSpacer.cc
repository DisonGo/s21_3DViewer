#include "Spacers/DrawConfigSpacer.h"
namespace s21 {
DrawConfigSpacer::DrawConfigSpacer(QObject* parent) : QObject(parent) {
  config_ = &DrawConfig::Instance();
  qDebug() << "Spacer config:" << config_;
};
}  // namespace s21
