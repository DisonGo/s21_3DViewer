#include <Logger.h>

#include <QDebug>
#include <cstdio>
#include <iostream>
// BUG Sometimes crashes when a lot of log messages in a short time
// Probably bc of delete[] c_str in CreateMessage method.
using std::cout;
#ifndef _WIN32
constexpr const char* RESET = "\033[0m";
constexpr const char* BLACK = "\033[30m";
constexpr const char* RED = "\033[31m";
constexpr const char* DARK_RED = "\033[31;2m";
constexpr const char* GREEN = "\033[32m";
constexpr const char* YELLOW = "\033[33m";
constexpr const char* BLUE = "\033[34m";
constexpr const char* MAGENTA = "\033[35m";
constexpr const char* CYAN = "\033[36m";
constexpr const char* WHITE = "\033[37m";
static const std::map<s21::Logger::LogLevel, const char*> level_color_map = {
    {s21::Logger::LogLevel::kBasic, WHITE},
    {s21::Logger::LogLevel::kInfo, BLUE},
    {s21::Logger::LogLevel::kWarning, YELLOW},
    {s21::Logger::LogLevel::kError, RED},
    {s21::Logger::LogLevel::kCritical, DARK_RED}};
#else
#include <colors.hpp>
static const std::map<s21::Logger::LogLevel, const char*> level_color_map = {
    {s21::Logger::LogLevel::kBasic, "white"},
    {s21::Logger::LogLevel::kInfo, "blue"},
    {s21::Logger::LogLevel::kWarning, "yellow"},
    {s21::Logger::LogLevel::kError, "red"},
    {s21::Logger::LogLevel::kCritical, "red_on_light_yellow"}};
#endif
// using color_os = std::function<std::ostream &(std::ostream &)>;
static const std::map<s21::Logger::LogLevel, const char*> prefix_map = {
    {s21::Logger::LogLevel::kBasic, "[Basic]"},
    {s21::Logger::LogLevel::kInfo, "[Info]"},
    {s21::Logger::LogLevel::kWarning, "[Warning]"},
    {s21::Logger::LogLevel::kError, "[Error]"},
    {s21::Logger::LogLevel::kCritical, "[Critical]"}};

namespace s21 {
Logger::LogLevel Logger::active_log_level_ = static_cast<LogLevel>(
    BIT(LogLevel::kBasic) | BIT(LogLevel::kInfo) | BIT(LogLevel::kWarning) |
    BIT(LogLevel::kError) | BIT(LogLevel::kCritical));
void Logger::Log(const char* message, LogLevel level, LogWriter writer) {
  if (!IsLogLevelActive(level)) return;
  auto str = CreateMessage(message, level);

#ifndef _WIN32
  if (writer == LogWriter::kCout)
    cout << level_color_map.at(level) << str << RESET << "\n";
#else
  auto msg = str.c_str();
  if (writer == LogWriter::kCout)
    cout << dye::colorize(msg, level_color_map.at(level)) << "\n";
#endif
}

void Logger::SetNameSpace(const std::string& name_space) {
  name_space_ = name_space;
}

std::string Logger::CreateMessage(const char* message, LogLevel level) {
  size_t c_msg_size = strlen(message) + 30;
  static size_t name_space_max_size_ = 1;
  name_space_max_size_ = std::max(name_space_max_size_, name_space_.size() + 2);
  char* c_msg = new char[c_msg_size];
  auto namespace_str = name_space_ + "::";
  const char* namespace_c_str = namespace_str.c_str();
  std::sprintf(c_msg, "%-10s %-*s %s", prefix_map.at(level),
               (int)name_space_max_size_, namespace_c_str, message);
  auto msg = std::string(c_msg);
  return msg;
}

}  // namespace s21
