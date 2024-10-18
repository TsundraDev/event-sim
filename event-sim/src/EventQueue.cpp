#include "EventQueue.hpp"

#include <cassert>
#include <cstdio>

EventQueue::EventQueue() :
  m_tick(0),
  m_max_tick(0x1000),
  m_event_queue(std::list<Event>()) {}

EventQueue::~EventQueue() {

}

void EventQueue::addEvent(Event event) {
  std::list<Event>::iterator it;
  for (it = m_event_queue.begin(); it != m_event_queue.end(); it++) {
    // Append event to last event with same tick
    if (it->tick() > event.tick()) {
      m_event_queue.insert(it, event);
      return;
    }
  }
  m_event_queue.push_back(event);
}

void EventQueue::run() {
  printf("Start simulation\n");
  while (!m_event_queue.empty()) {
    // Finish simulation early
    if (!(m_tick < m_max_tick)) {
      printf("Finish simulation early [max_tick: %ld]\n", m_max_tick);
      break;
    }

    // Update time
    Event event = m_event_queue.front();
    assert(m_tick <= event.tick());
    if (m_tick < event.tick()) {
      m_tick = event.tick();
    }

    // Resolve event
    event.resolve();
    m_event_queue.pop_front();
  }

  // Check no more updates necessary
  printf("Finish simulation at tick %ld\n", m_tick);
}

void EventQueue::runTick(uint64_t tick) {
  while (!m_event_queue.empty()) {
    // Finish simulation early
    if (!(m_tick < m_max_tick)) {
      printf("Finish simulation early [max_tick: %ld]\n", m_max_tick);
      break;
    }

    // Check if we've overstepped
    Event event = m_event_queue.front();
    assert(m_tick <= event.tick());
    if (event.tick() >= tick) return;

    // Update time
    if (m_tick < event.tick()) {
      m_tick = event.tick();
    }

    // Resolve event
    event.resolve();
    m_event_queue.pop_front();
  }
}
