#include "Logger.hpp"

#include <cassert>
#include <list>
#include <string>

#include <Log/LogBook.hpp>
#include <Log/LogLevel.hpp>
#include <Log/LogTag.hpp>

// -------------------------------------------------------------------------------------------------
// -- Logger constructor and destructor
// -------------------------------------------------------------------------------------------------
Logger::Logger() :
  m_tag(LogTag()),
  m_logbook_list(std::list<LogBook*>()) {}

Logger::Logger(LogTag tag) :
  m_tag(tag),
  m_logbook_list(std::list<LogBook*>()) {}

Logger::~Logger() {
  this->clearLogBookList();
}


// -------------------------------------------------------------------------------------------------
// -- Manage LogBook list
// -------------------------------------------------------------------------------------------------
bool Logger::addLogBook(LogBook* logbook) {
  // Sanity check
  assert(logbook != nullptr);

  // Check for duplicate
  std::list<LogBook*>::iterator it;
  for (it = m_logbook_list.begin(); it != m_logbook_list.end(); it++) {
    if ((*it) == logbook) {
      // Duplicate found
      fprintf(stderr, "[ WARN] [C-LOG] [LOGGER] - Attempted to add duplicate LogBook\n");
      return false;
    }
  }

  logbook->addLogger(this);
  m_logbook_list.push_back(logbook);
  return true;
}

bool Logger::removeLogBook(LogBook* logbook) {
  // Sanity check
  assert(logbook != nullptr);

  // Find LogBook
  std::list<LogBook*>::iterator it;
  for (it = m_logbook_list.begin(); it != m_logbook_list.end(); it++) {
    if ((*it) == logbook) {
      // LogBook found
      (*it)->removeLoggerEntry(this);
      m_logbook_list.erase(it);
      return true;
    }
  }

  fprintf(stderr, "[ WARN] [C-LOG] [LOGGER] - Attempted to remove unknown LogBook\n");
  return false;
}

void Logger::clearLogBookList() {
  while (!m_logbook_list.empty()) {
    m_logbook_list.front()->removeLoggerEntry(this);
    m_logbook_list.pop_front();
  }
}

bool Logger::removeLogBookEntry(LogBook* logbook) {
  // Sanity check
  assert(logbook != nullptr);

  // Find LogBook
  std::list<LogBook*>::iterator it;
  for (it = m_logbook_list.begin(); it != m_logbook_list.end(); it++) {
    if ((*it) == logbook) {
      // LogBook found
      m_logbook_list.erase(it);
      return true;
    }
  }

  fprintf(stderr, "[ WARN] [C-LOG] [LOGGER] - Attempted to remove unknown LogBook\n");
  return false;
}


// -------------------------------------------------------------------------------------------------
// -- Logging
// -------------------------------------------------------------------------------------------------
void Logger::log(LogLevel level, std::string message) {
  std::list<LogBook*>::iterator it;
  for (it = m_logbook_list.begin(); it != m_logbook_list.end(); it++) {
    (*it)->log(level, m_tag, message);
  }
}


