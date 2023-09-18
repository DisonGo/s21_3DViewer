#ifndef LOGGER_H
#define LOGGER_H
#include <map>
#include <string>

#define BIT(x) static_cast<int>(x)
namespace s21 {
class Logger {
 public:
  Logger() = default;
  Logger(const std::string& name_space) : name_space_(name_space){};
  ~Logger() = default;
  enum class LogLevel {
    kBasic = 1,
    kInfo = 1 << 1,
    kWarning = 1 << 2,
    kError = 1 << 3,
    kCritical = 1 << 4
  };
  enum class LogWriter { kCout, kQDebug };
  void Log(const std::string& message, LogLevel level = LogLevel::kBasic,
           LogWriter writer = LogWriter::kCout);
  void SetNameSpace(const std::string& name_space);
  static bool IsLogLevelActive(LogLevel level) {
    return BIT(active_log_level_) & BIT(level);
  }
  static void ActivateLogLevel(LogLevel level) {
    if (!IsLogLevelActive(level))
      active_log_level_ =
          static_cast<LogLevel>(BIT(active_log_level_) | BIT(level));
  }
  static void DeactivateLogLevel(LogLevel level) {
    if (IsLogLevelActive(level))
      active_log_level_ =
          static_cast<LogLevel>(BIT(active_log_level_) & ~BIT(level));
  }

 private:
  static LogLevel active_log_level_;
  std::string name_space_ = "";
  std::string CreateMessage(const std::string& message, LogLevel level);
};

}  // namespace s21
#endif  // LOGGER_H
