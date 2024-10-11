#include <cstdio>

#include <EventSim.hpp>

int main() {

  EventQueue event_queue = EventQueue();

  Agent ag1 = Agent(&event_queue);
  Agent ag2 = Agent(&event_queue);

  ag1.createEvent(Event(0));
  ag1.createEvent(Event(0, &ag2, nullptr, 0));

  event_queue.run();

  return 0;
}
