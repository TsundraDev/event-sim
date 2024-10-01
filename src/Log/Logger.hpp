#ifndef __LOG__LOGGER_HPP__
#define __LOG__LOGGER_HPP__

#include <list>
#include <string>

#include "LogBook.hpp"
#include "LogLevel.hpp"
#include "LogTag.hpp"

// -------------------------------------------------------------------------------------------------
// -- Logger class
// -------------------------------------------------------------------------------------------------
class Logger {
private:
  LogTag m_tag;

  std::list<LogBook*> m_logbook_list;

public:
  // Logger constructor and destructor
  Logger();
  Logger(LogTag tag);
  ~Logger();

  // Manage LogBook list
  bool addLogBook(LogBook* logbook);
  bool removeLogBook(LogBook* logbook);
  void clearLogBookList();

  bool removeLogBookEntry(LogBook* logbook);

  // Logging
  void log(LogLevel level, std::string message);
};

#endif
