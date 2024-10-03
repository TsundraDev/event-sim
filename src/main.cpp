#include <cstdio>

#include <EventSim/EventSim.hpp>

int main() {

  printf("event-sim\n");

  EventQueue event_queue = EventQueue();

  Agent ag1 = Agent(&event_queue);
  Agent ag2 = Agent(&event_queue);

  ag1.createEvent(10);

  printf("Start simulation\n");
  event_queue.run();
  printf("Finish simulation\n");

  return 0;
}
