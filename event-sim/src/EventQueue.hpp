#ifndef __EVENTSIM__EVENTQUEUE_HPP__
#define __EVENTSIM__EVENTQUEUE_HPP__

#include <cstdint>
#include <list>

#include "Event.hpp"

class EventQueue {
private:
  uint64_t            m_tick;
  uint64_t            m_max_tick;
  std::list<Event>    m_event_queue;


public:
  EventQueue();
  ~EventQueue();

  uint64_t tick() { return m_tick; }

  void addEvent(Event event);
  void run();
};


#endif
