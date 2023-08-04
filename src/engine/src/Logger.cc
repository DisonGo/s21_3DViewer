#include <Logger.h>
#include <QDebug>
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
static const std::map<s21::Logger::LogLevel, const char*> prefix_map = {
    {s21::Logger::LogLevel::kBasic, "[Basic]"},
    {s21::Logger::LogLevel::kInfo, "[Info]"},
    {s21::Logger::LogLevel::kWarning, "[Warning]"},
    {s21::Logger::LogLevel::kError, "[Error]"},
    {s21::Logger::LogLevel::kCritical, "[Critical]"}};

static const std::map<s21::Logger::LogLevel, const char*> level_color_map = {
    {s21::Logger::LogLevel::kBasic, WHITE},
    {s21::Logger::LogLevel::kInfo, BLUE},
    {s21::Logger::LogLevel::kWarning, YELLOW},
    {s21::Logger::LogLevel::kError, RED},
    {s21::Logger::LogLevel::kCritical, DARK_RED}};

namespace s21 {

void Logger::Log(const char *message, LogLevel level, LogWriter writer)
{

    auto str = CreateMessage(message, level);
    auto msg = str.c_str();
    if (writer == LogWriter::kCout)
        cout << msg << "\n";
    if (writer == LogWriter::kQDebug)
        qDebug() << msg;
}

void Logger::SetNameSpace(const std::string &name_space)
{
    name_space_ = name_space;
}

std::string Logger::CreateMessage(const char *message, LogLevel level)
{
    auto msg = std::string(level_color_map.at(level));
    msg += prefix_map.at(level);
    msg += "\t";
    msg += name_space_ + "::";
    msg += "\t";
    msg += message;
    msg += RESET;
    return msg;
}

}
