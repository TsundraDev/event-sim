#ifndef __EVENTSIM__AGENT_HPP__
#define __EVENTSIM__AGENT_HPP__

#include <cstdint>

class Event;
class EventQueue;

class Agent {
private:
  EventQueue* m_event_queue;

public:
  Agent(EventQueue* event_queue);
  ~Agent();

  void createEvent(Event event);
  void recvEvent(uint8_t* data, uint64_t size);
};

#endif
