#include <cstdio>

#include <EventSim.hpp>

class Clock : public Agent {
public:
  Clock(EventQueue* event_queue) : Agent(event_queue) {}
  void init() { this->createEvent(Event(0, (Agent*)this, nullptr, 0)); }
  void recvEvent(uint8_t* data, uint64_t size) {
    printf("[%ld] Clock\n", m_event_queue->tick());
    uint64_t send_tick = m_event_queue->tick() + 1;
    this->createEvent(Event(send_tick, (Agent*)this, nullptr, 0)); 
  }
};

int main() {

  EventQueue event_queue = EventQueue();

  Clock clock = Clock(&event_queue);
  clock.init();
  event_queue.run();

  return 0;
}
