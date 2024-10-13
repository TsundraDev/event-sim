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
  uint64_t                m_tick;
  Agent*                  m_src;
  std::vector<EventEntry> m_event_data;

public:
  Event(uint64_t tick, Agent* src, Agent* dest);
  Event(uint64_t tick, Agent* src, Agent* dest, uint8_t* data, uint64_t size);

  uint64_t                tick()      { return m_tick; };
  std::vector<EventEntry> eventData() { return m_event_data;}

  void addEntry(Agent* dest, uint8_t* data, uint64_t size);
  void resolve();
};

#endif
