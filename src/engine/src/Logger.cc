#include <Logger.h>

#include <QDebug>
#include <colors.hpp>
#include <cstdio>
#include <iostream>

using std::cout;
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
// using color_os = std::function<std::ostream &(std::ostream &)>;
static const std::map<s21::Logger::LogLevel, const char*> prefix_map = {
    {s21::Logger::LogLevel::kBasic, "[Basic]"},
    {s21::Logger::LogLevel::kInfo, "[Info]"},
    {s21::Logger::LogLevel::kWarning, "[Warning]"},
    {s21::Logger::LogLevel::kError, "[Error]"},
    {s21::Logger::LogLevel::kCritical, "[Critical]"}};

static const std::map<s21::Logger::LogLevel, const char*> level_color_map = {
    {s21::Logger::LogLevel::kBasic, "white"},
    {s21::Logger::LogLevel::kInfo, "blue"},
    {s21::Logger::LogLevel::kWarning, "yellow"},
    {s21::Logger::LogLevel::kError, "red"},
    {s21::Logger::LogLevel::kCritical, "red_on_light_yellow"}};

namespace s21 {

void Logger::Log(const char* message, LogLevel level, LogWriter writer) {
  auto str = CreateMessage(message, level);
  auto msg = str.c_str();
  if (writer == LogWriter::kCout)
    cout << dye::colorize(msg, level_color_map.at(level)) << "\n";
  //  if (writer == LogWriter::kQDebug) qDebug() << dye::red(msg) << msg;
}

void Logger::SetNameSpace(const std::string& name_space) {
  name_space_ = name_space;
}

std::string Logger::CreateMessage(const char* message, LogLevel level) {
  size_t c_msg_size = strlen(message) + 30;
  static size_t name_space_max_size_ = 10;
  name_space_max_size_ = std::max(name_space_max_size_, name_space_.size());
  char* c_msg = new char[c_msg_size];
  // sprintf_s(c_msg, c_msg_size, "%20s\t %*s::\t %s", prefix_map.at(level),
  //           name_space_max_size_, name_space_.c_str(), message);
  sprintf(c_msg, "%20s\t %*s::\t %s", prefix_map.at(level),
          (int)name_space_max_size_, name_space_.c_str(), message);
  cout << dye::colorize(c_msg, level_color_map.at(level)) << "\n";
  auto msg = std::string();
  msg.assign(c_msg);
  return msg;
}

}  // namespace s21
