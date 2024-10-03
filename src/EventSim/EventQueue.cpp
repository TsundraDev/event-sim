#include "EventQueue.hpp"

#include <cassert>
#include <cstdio>

EventQueue::EventQueue() :
  m_time(0),
  m_event_queue(std::list<Event>()){}

EventQueue::~EventQueue() {

}

void EventQueue::addEvent(Event event) {
  std::list<Event>::iterator it;
  for (it = m_event_queue.begin(); it != m_event_queue.end(); it++) {
    std::list<Event>::iterator next = std::next(it, 1);
    if (next == m_event_queue.end()) {
      if (it->time() <= event.time()) m_event_queue.push_back(event);
      else m_event_queue.insert(it, event);
      return;
    }
    if (next->time() > event.time()) {
      m_event_queue.insert(it, event);
      return;
    }
  }
  m_event_queue.push_back(event);
}

void EventQueue::run() {
  printf("Start simulation\n");
  while (!m_event_queue.empty()) {
    Event event = m_event_queue.front();

    // Update time
    assert(m_time <= event.time());
    m_time = event.time();

    // Resolve event
    event.resolve();
    m_event_queue.pop_front();
  } 

  printf("Finish simulation at cycle %ld\n", m_time);
}
