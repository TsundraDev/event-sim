#ifndef __EVENTSIM__EVENTQUEUE_HPP__
#define __EVENTSIM__EVENTQUEUE_HPP__

#include <cstdint>
#include <list>

#include "Event.hpp"

class EventQueue {
private:
  uint64_t m_time;
  std::list<Event> m_event_queue;

public:
  EventQueue();
  ~EventQueue();

  void addEvent(Event event);

  void run();
};


#endif
