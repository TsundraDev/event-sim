#ifndef __EVENTSIM__AGENT_HPP__
#define __EVENTSIM__AGENT_HPP__

#include <cstdint>
#include <vector>

class EventEntry;
class Event;
class EventQueue;

class Agent {
private:
  EventQueue* m_event_queue;
  std::vector<EventEntry> m_inbox;

public:
  Agent(EventQueue* event_queue);
  ~Agent();

  void createEvent(Event event);
  void recvEvent(uint8_t* data, uint64_t size);

  void update();
};

#endif
