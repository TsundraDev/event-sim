#include "EventQueue.hpp"

EventQueue::EventQueue() :
  m_time(0),
  m_event_queue(std::list<Event>()){}

EventQueue::~EventQueue() {

}

void EventQueue::addEvent(Event event) {
  std::list<Event>::iterator it;
  for (it = m_event_queue.begin(); it != m_event_queue.end(); it++) {
    std::list<Event>::iterator next = std::next(it, 1);
    if (next->time() > it->time()) {
      m_event_queue.insert(it, event);
      return;
    }
  }
  m_event_queue.push_back(event);
}

void EventQueue::run() {
  while (!m_event_queue.empty()) {
    Event event = m_event_queue.front();
    event.resolve();

    // Remove event
    m_event_queue.pop_front();
  } 
}
