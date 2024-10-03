#include "Agent.hpp"

#include <cstdio>

#include "Event.hpp"
#include "EventQueue.hpp"

Agent::Agent(EventQueue* event_queue) :
  m_event_queue(event_queue) {}

Agent::~Agent() {

}

void Agent::createEvent(Event event) {
  m_event_queue->addEvent(event);
}

void Agent::recvEvent([[maybe_unused]] uint8_t* data, [[maybe_unused]] uint64_t size) {
  printf("Received event\n");
}
