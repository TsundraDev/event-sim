#ifndef __EVENTSIM__AGENT_HPP__
#define __EVENTSIM__AGENT_HPP__

#include <cstdint>
#include <vector>

class EventEntry;
class Event;
class EventQueue;

class Agent {
protected:
  EventQueue* m_event_queue;

public:
  Agent(EventQueue* event_queue);
  ~Agent();

  void createEvent(Event event);
  virtual void recvEvent(Agent* src, uint8_t* data, uint64_t size);
};

#endif
