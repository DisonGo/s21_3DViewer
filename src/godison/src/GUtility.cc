#include <godison/GUtility.h>

namespace godison {
namespace utility {
float GToRadians(float degrees) { return degrees * M_PI / 180; }
float GToDegrees(float radians) { return radians * 180 / M_PI; }
}  // namespace utility
}  // namespace godison