#ifndef __LOG__LOGSYSTEM_HPP__
#define __LOG__LOGSYSTEM_HPP__

#include <cassert>
#include <cstdint>
#include <format>
#include <string>
#include <vector>

#include "LogBook.hpp"
#include "Logger.hpp"

// -------------------------------------------------------------------------------------------------
// -- LogSystem class
// -------------------------------------------------------------------------------------------------
typedef int8_t LogBookID;
typedef int8_t LoggerID;

#define INVALID_LOGBOOK_ID -1;
#define INVALID_LOGGER_ID  -1;


class LogSystem {
private:
  std::vector<std::pair<bool, LogBook>> m_logbook_list;
  std::vector<std::pair<bool, Logger>>  m_logger_list;

  static bool    m_init;
  static LogBook m_logbook;
  static Logger  m_logger;

public:
  LogSystem();
  ~LogSystem();

  // Set default Logging
  void setLogLevel(LogLevel level);

  // Manage LogBook list
  LogBookID addLogBook(LogLevel level);
  LogBookID addLogBook(LogLevel level, std::string outfile);
  void removeLogBook(LogBookID logbook);
  void clearLogBookList();

  // Manage Logger list
  LoggerID addLogger();
  LoggerID addLogger(LogTag tag);
  void removeLogger(LoggerID logger);
  void clearLoggerList();

  // Linking Logger to LogBook
  bool link(LogBookID logbook, LoggerID logger);
  bool unlink(LogBookID logbook, LoggerID logger);

  // Manage LogEntry
  #define LOGSYSTEM_LOG_FUNCTION_DECLARATION(func_name) \
  template<typename... Args> \
  void func_name(LoggerID logger, const std::format_string<Args...> fmt, Args&&... args);

  LOGSYSTEM_LOG_FUNCTION_DECLARATION(fatal);
  LOGSYSTEM_LOG_FUNCTION_DECLARATION(error);
  LOGSYSTEM_LOG_FUNCTION_DECLARATION(warn);
  LOGSYSTEM_LOG_FUNCTION_DECLARATION(info);
  LOGSYSTEM_LOG_FUNCTION_DECLARATION(debug);

  #define LOGSYSTEM_DEFAULT_LOG_FUNCTION_DECLARATION(func_name) \
  template<typename... Args> \
  void func_name(const std::format_string<Args...> fmt, Args&&... args);

  LOGSYSTEM_DEFAULT_LOG_FUNCTION_DECLARATION(fatal);
  LOGSYSTEM_DEFAULT_LOG_FUNCTION_DECLARATION(error);
  LOGSYSTEM_DEFAULT_LOG_FUNCTION_DECLARATION(warn);
  LOGSYSTEM_DEFAULT_LOG_FUNCTION_DECLARATION(info);
  LOGSYSTEM_DEFAULT_LOG_FUNCTION_DECLARATION(debug);

  bool output(LogBookID logbook);
  
};

// -------------------------------------------------------------------------------------------------
// -- LogSystem : Logging functions
// -------------------------------------------------------------------------------------------------
#define LOGSYSTEM_LOG_FUNCTION_IMPLEMENTATION(func_name, log_level) \
template<typename... Args> \
void LogSystem::func_name(LoggerID logger, const std::format_string<Args...> fmt, Args&&... args) { \
  assert(logger < (int64_t)m_logger_list.size()); \
  assert(m_logger_list[logger].first); \
  m_logger_list[logger].second.log(log_level, \
                                   std::vformat(fmt.get(), std::make_format_args(args...))); \
}

LOGSYSTEM_LOG_FUNCTION_IMPLEMENTATION(fatal, LogLevel::FATAL);
LOGSYSTEM_LOG_FUNCTION_IMPLEMENTATION(error, LogLevel::ERROR);
LOGSYSTEM_LOG_FUNCTION_IMPLEMENTATION(warn,  LogLevel::WARN);
LOGSYSTEM_LOG_FUNCTION_IMPLEMENTATION(info,  LogLevel::INFO);
LOGSYSTEM_LOG_FUNCTION_IMPLEMENTATION(debug, LogLevel::DEBUG);

#define LOGSYSTEM_DEFAULT_LOG_FUNCTION_IMPLEMENTATION(func_name, log_level) \
template<typename... Args> \
void LogSystem::func_name(const std::format_string<Args...> fmt, Args&&... args) { \
  m_logger.log(log_level, std::vformat(fmt.get(), std::make_format_args(args...))); \
}

LOGSYSTEM_DEFAULT_LOG_FUNCTION_IMPLEMENTATION(fatal, LogLevel::FATAL);
LOGSYSTEM_DEFAULT_LOG_FUNCTION_IMPLEMENTATION(error, LogLevel::ERROR);
LOGSYSTEM_DEFAULT_LOG_FUNCTION_IMPLEMENTATION(warn,  LogLevel::WARN);
LOGSYSTEM_DEFAULT_LOG_FUNCTION_IMPLEMENTATION(info,  LogLevel::INFO);
LOGSYSTEM_DEFAULT_LOG_FUNCTION_IMPLEMENTATION(debug, LogLevel::DEBUG);

#endif
