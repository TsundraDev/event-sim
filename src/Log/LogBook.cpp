#include "LogBook.hpp"

#include <cassert>
#include <list>
#include <queue>
#include <string>

#include <Log/LogEntry.hpp>
#include <Log/LogLevel.hpp>
#include <Log/Logger.hpp>

// -------------------------------------------------------------------------------------------------
// -- LogBook constructor and destructor
// -------------------------------------------------------------------------------------------------
LogBook::LogBook(LogLevel level) :
  m_level(level),
  m_outfile(""),
  m_logger_list(std::list<Logger*>()),
  m_logbook(std::queue<LogEntry>()) {}

LogBook::LogBook(LogLevel level, std::string outfile) :
  m_level(level),
  m_outfile(outfile),
  m_logger_list(std::list<Logger*>()),
  m_logbook(std::queue<LogEntry>()) {}

LogBook::~LogBook() {
  // Output all LogEntry and remove Logger
  this->output();
  this->clearLogger();

  // Check for lost data
  if (!m_logbook.empty()) {
    fprintf(stderr, "[ERROR] [C-LOG] [LOGBOOK] - Deleting LogBook with remaining logs\n");
  }
}


// -------------------------------------------------------------------------------------------------
// -- Manage Logger list
// -------------------------------------------------------------------------------------------------
bool LogBook::addLogger(Logger* logger) {
  // Sanity check
  assert(logger != nullptr);

  // Check for duplicate
  std::list<Logger*>::iterator it;
  for (it = m_logger_list.begin(); it != m_logger_list.end(); it++) {
    if ((*it) == logger) {
      // Duplicate found
      fprintf(stderr, "[ WARN] [C-LOG] [LOGBOOK] - Attempted to add duplicate Logger\n");
      return false;
    }
  }

  m_logger_list.push_back(logger);
  return true;
}

bool LogBook::removeLogger(Logger* logger) {
  // Sanity check
  assert(logger != nullptr);

  // Find Logger
  std::list<Logger*>::iterator it;
  for (it = m_logger_list.begin(); it != m_logger_list.end(); it++) {
    if ((*it) == logger) {
      // Logger found
      logger->removeLogBookEntry(this);
      m_logger_list.erase(it);
      return true;
    }
  }

  fprintf(stderr, "[ WARN] [C-LOG] [LOGBOOK] - Attempted to remove unknown Logger\n");
  return false;
}

void LogBook::clearLogger() {
  while (!m_logger_list.empty()) {
    m_logger_list.front()->removeLogBookEntry(this);
    m_logger_list.pop_front();
  }
}

bool LogBook::removeLoggerEntry(Logger* logger) {
  // Sanity check
  assert(logger != nullptr);

  // Find Logger
  std::list<Logger*>::iterator it;
  for (it = m_logger_list.begin(); it != m_logger_list.end(); it++) {
    if ((*it) == logger) {
      // Logger found
      m_logger_list.erase(it);
      return true;
    }
  }

  fprintf(stderr, "[ WARN] [C-LOG] [LOGBOOK] - Attempted to remove unknown Logger\n");
  return false;
}


// -------------------------------------------------------------------------------------------------
// -- Manage LogEntry
// -------------------------------------------------------------------------------------------------
void LogBook::log(LogLevel level, LogTag tag, std::string message) {
  LogEntry log_entry = {level, tag, message};
  m_logbook.push(log_entry);

  // Output if fatal or debug
  if (level == LogLevel::FATAL || level == LogLevel::DEBUG) this->output();
}

bool LogBook::output() {
  // Open file
  FILE* f = (m_outfile == "") ? stderr : fopen(m_outfile.c_str(), "a");
  if (f == nullptr) {
    fprintf(stderr, "[ WARN] [C-LOG] [LOGBOOK] - Unable to open file %s\n", m_outfile.c_str());
    return false;
  }

  // Output LogEntry
  while (!m_logbook.empty()) {
    LogEntry log_entry = m_logbook.front();

    // Check if log is important
    if (log_entry.level.important(m_level)) {
      // Attempt to output
      if (fprintf(f, "%s\n", this->logEntryString(log_entry).c_str()) < 0) {
        fprintf(stderr, "[ WARN] [C-LOG] [LOGBOOK] - Unable to write to file %s\n", m_outfile.c_str());
        if (f != stderr) fclose(f);
        return false;
      }
    }

    m_logbook.pop();
  }

  if (f != stderr) fclose(f);
  return true;
}

std::string LogBook::logEntryString(LogEntry log_entry) {
  std::string buffer;
  switch (log_entry.level) {
    case LogLevel::FATAL : buffer = "[FATAL] "; break;
    case LogLevel::ERROR : buffer = "[ERROR] "; break;
    case LogLevel::WARN  : buffer = "[ WARN] "; break;
    case LogLevel::INFO  : buffer = "[ INFO] "; break;
    case LogLevel::DEBUG : buffer = "[DEBUG] "; break;
  }

  if (log_entry.tag.module() != "") {
    buffer += log_entry.tag.getString() + " ";
  }

  buffer += log_entry.message;
  return buffer;
}
