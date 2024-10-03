#include "Event.hpp"

Event::Event(uint64_t time) :
  m_time(time),
  m_event_data(std::vector<EventEntry>()) {}

void Event::addEntry(Agent* agent, uint8_t* data, uint64_t size) {
  EventEntry entry = {agent, data, size};
  m_event_data.push_back(entry);
}

void Event::resolve() {
  for (uint64_t i = 0; i < m_event_data.size(); i++) {
    Agent*   agent = m_event_data[i].agent;
    uint8_t* data  = m_event_data[i].data;
    uint64_t size  = m_event_data[i].size;
    if (agent != nullptr) {
      agent->recvEvent(data, size);
      // Delete data on exit
      if (data != nullptr) delete data;
    }
  }
}
