#include "EventQueue.hpp"

#include <cassert>
#include <cstdio>

EventQueue::EventQueue() :
  m_time(0),
  m_event_queue(std::list<Event>()),
  m_update_agent_list(std::vector<Agent*>()) {}

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
  while (!m_event_queue.empty() || !m_update_agent_list.empty()) {
    // If EventQueue is empty, update agents and retry
    if (m_event_queue.empty()) {
      this->updateAgents();
      continue;
    }

    // Get current time
    Event event = m_event_queue.front();
    uint64_t event_time = event.time();

    // If time has moved, update all relevant agents
    assert(m_time <= event_time);
    if (m_time < event_time) {
      this->updateAgents();
      m_time = event.time();
    }

    // Get agents to update
    std::vector<EventEntry> event_data = event.eventData();
    for (uint64_t i = 0; i < event_data.size(); i++) {
      // Find duplicate
      bool find_duplicate = false;
      for (uint64_t j = 0; j < m_update_agent_list.size(); j++) {
        //printf("j : %ld; size : %ld\n", j, m_update_agent_list.size());
        if (event_data[i].agent == m_update_agent_list[j]) {
          find_duplicate = true;
          continue;
        }
      }

      // Update update agent list
      if (!find_duplicate) m_update_agent_list.push_back(event_data[i].agent);
    }

    // Resolve event
    event.resolve();
    m_event_queue.pop_front();
  }

  // Check no more updates necessary
  printf("Finish simulation at cycle %ld\n", m_time);
}

void EventQueue::updateAgents() {
  for (uint64_t i = 0; i < m_update_agent_list.size(); i++) {
    m_update_agent_list[i]->update();
  }
  m_update_agent_list.clear();
}
