#ifndef LOGGER_H
#define LOGGER_H
#include <map>
#include <string>
namespace s21 {
class Logger {
 public:
  Logger() = default;
  Logger(const std::string& name_space) : name_space_(name_space){};
  ~Logger() = default;
  enum class LogLevel { kBasic, kInfo, kWarning, kError, kCritical };
  enum class LogWriter { kCout, kQDebug };
  void Log(const char* message, LogLevel level = LogLevel::kBasic,
                  LogWriter writer = LogWriter::kQDebug);
  void SetNameSpace(const std::string& name_space);
private:
  std::string name_space_ = "";
  std::string CreateMessage(const char* message, LogLevel level);
};
}  // namespace s21
#endif  // LOGGER_H
