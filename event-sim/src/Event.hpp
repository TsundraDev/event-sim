#ifndef __EVENTSIM__EVENT_HPP__
#define __EVENTSIM__EVENT_HPP__

#include <cstdint>
#include <list>
#include <vector>

#include "Agent.hpp"

struct EventEntry {
  Agent*   agent;
  uint8_t* data;
  uint64_t size;
};

class Event {
private:
  uint64_t                m_time;
  std::vector<EventEntry> m_event_data;

public:
  Event(uint64_t time);
  Event(uint64_t time, Agent* agent, uint8_t* data, uint64_t size);

  uint64_t                time()      { return m_time; };
  std::vector<EventEntry> eventData() { return m_event_data;}

  void addEntry(Agent* agent, uint8_t* data, uint64_t size);
  void resolve();
};

#endif
