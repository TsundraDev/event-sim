#include "Agent.hpp"

#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "Event.hpp"
#include "EventQueue.hpp"

Agent::Agent(EventQueue* event_queue) :
  m_event_queue(event_queue) {}

Agent::~Agent() {

}

void Agent::createEvent(Event event) {
  m_event_queue->addEvent(event);
}

void Agent::recvEvent(Agent* src, uint8_t* data, uint64_t size) {
  fprintf(stderr, "Unimplemented Agent::recvEvent\n");
  exit(1);
}

