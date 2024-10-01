#ifndef __LOG__LOGTAG_HPP__
#define __LOG__LOGTAG_HPP__

#include <string>

// -------------------------------------------------------------------------------------------------
// -- LogTag class
// -------------------------------------------------------------------------------------------------
class LogTag {
private:
  std::string m_module;
  std::string m_submodule;

public:
  LogTag()                                          : m_module(""),     m_submodule("") {}
  LogTag(std::string module)                        : m_module(module), m_submodule("") {}
  LogTag(std::string module, std::string submodule) : m_module(module), m_submodule(submodule) {}

  std::string module()    { return m_module;    }
  std::string submodule() { return m_submodule; }

  std::string getString() {
    std::string string = "";
    if (m_module != "")    string += "[" + m_module + "]";
    if (m_submodule != "") string += " [" + m_submodule + "]";
    return string;
  }
};


#endif
