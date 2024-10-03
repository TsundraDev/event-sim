#include <cstdio>

#include <EventSim/EventSim.hpp>

int main() {

  EventQueue event_queue = EventQueue();

  Agent ag1 = Agent(&event_queue);
  Agent ag2 = Agent(&event_queue);

  ag1.createEvent(Event(10));
  ag1.createEvent(Event(1));
  ag1.createEvent(Event(10));
  ag1.createEvent(Event(20));
  ag1.createEvent(Event(10));

  event_queue.run();

  return 0;
}
