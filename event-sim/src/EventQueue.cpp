#include "EventQueue.hpp"

#include <cassert>
#include <cstdio>

EventQueue::EventQueue() :
  m_time(0),
  m_max_time(100),
  m_event_queue(std::list<Event>()) {}

EventQueue::~EventQueue() {

}

void EventQueue::addEvent(Event event) {
  std::list<Event>::iterator it;
  for (it = m_event_queue.begin(); it != m_event_queue.end(); it++) {
    if (it->time() > event.time()) {
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
    if (m_time >= m_max_time) {
      printf("Finish simulation early [max_cycles: %ld]\n", m_max_time);
      break;
    }
    // Get current time
    Event event = m_event_queue.front();

    // Update time
    assert(m_time <= event.time());
    if (m_time < event.time()) {
      m_time = event.time();
    }

    // Resolve event
    event.resolve();
    m_event_queue.pop_front();
  }

  // Check no more updates necessary
  printf("Finish simulation at cycle %ld\n", m_time);
}
