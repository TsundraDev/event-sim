#ifndef __LOG__LOGENTRY_HPP__
#define __LOG__LOGENTRY_HPP__

#include <string>

#include "LogLevel.hpp"
#include "LogTag.hpp"

// -------------------------------------------------------------------------------------------------
// -- LogEntry class
// -------------------------------------------------------------------------------------------------
typedef struct {
  LogLevel    level;
  LogTag      tag;
  std::string message;
} LogEntry;


#endif
