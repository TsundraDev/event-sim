#ifndef __EVENTSIM__AGENT_HPP__
#define __EVENTSIM__AGENT_HPP__

#include <cstdint>

class EventQueue;

class Agent {
private:
  EventQueue* m_event_queue;

public:
  Agent(EventQueue* event_queue);
  ~Agent();

  void createEvent(uint64_t time);
  void recvEvent(uint8_t* data, uint64_t size);
};

#endif
