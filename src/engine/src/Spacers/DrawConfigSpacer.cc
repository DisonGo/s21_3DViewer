#include "Spacers/DrawConfigSpacer.h"
namespace s21 {
DrawConfigSpacer::DrawConfigSpacer(DrawConfig& config, QObject* parent) : QObject(parent), config_(config) {
};
}  // namespace s21
