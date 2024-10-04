#include "Agent.hpp"

#include <cassert>
#include <cstdint>
#include <cstdio>
#include <vector>

#include "Event.hpp"
#include "EventQueue.hpp"

Agent::Agent(EventQueue* event_queue) :
  m_event_queue(event_queue),
  m_inbox(std::vector<EventEntry>()) {}

Agent::~Agent() {
  // Check Agent has no more messages
  assert(m_inbox.empty());
}

void Agent::createEvent(Event event) {
  m_event_queue->addEvent(event);
}

void Agent::recvEvent(uint8_t* data, uint64_t size) {
  EventEntry event = { nullptr, data, size };
  m_inbox.push_back(event);
}

void Agent::update() {
  // Currently ignore all messages
  m_inbox.clear();
}
