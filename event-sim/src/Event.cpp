#include "Event.hpp"
#include <cstdio>

Event::Event(uint64_t tick, Agent* src, Agent* dest) :
  m_tick(tick),
  m_src(src),
  m_event_data(std::vector<EventEntry>()) {
  EventEntry entry = {dest, nullptr, 0};
  m_event_data.push_back(entry);
}

Event::Event(uint64_t tick, Agent* src, Agent* dest, uint8_t* data, uint64_t size) :
  m_tick(tick),
  m_src(src),
  m_event_data(std::vector<EventEntry>()) {
  EventEntry entry = {dest, data, size};
  m_event_data.push_back(entry);
}


void Event::addEntry(Agent* dest, uint8_t* data, uint64_t size) {
  EventEntry entry = {dest, data, size};
  m_event_data.push_back(entry);
}

void Event::resolve() {
  for (uint64_t i = 0; i < m_event_data.size(); i++) {
    Agent*   dest = m_event_data[i].agent;
    uint8_t* data  = m_event_data[i].data;
    uint64_t size  = m_event_data[i].size;
    if (dest != nullptr) {
      dest->recvEvent(m_src, data, size);
      // Delete data on exit
      if (data != nullptr) delete data;
    }
  }
}
