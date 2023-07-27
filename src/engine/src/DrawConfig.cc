#include "DrawConfig.h"
namespace s21 {
DrawConfig& DrawConfig::Instance() {
  static DrawConfig instance;
  return instance;
}
}  // namespace s21