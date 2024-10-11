#include <cstdio>

#include <EventSim.hpp>

class UpdatePC;
class PC : public Agent {
private:
  UpdatePC* m_upc;
  uint64_t m_pc;

public:
  PC(EventQueue* event_queue) : Agent(event_queue), m_upc(nullptr), m_pc(0) {}

  void connect(UpdatePC* upc) { m_upc = upc; }
  void init() {
    uint64_t* data = new uint64_t;
    *data = m_pc;
    this->createEvent(Event(0, (Agent*)m_upc, (uint8_t*)data, 8));
  }

  void recvEvent(uint8_t* data, uint64_t size) {
    EventEntry event = { nullptr, data, size };
    printf("[%ld] Recv Event PC\n", m_event_queue->time());
    uint64_t recv_pc = *(uint64_t*)data;
    m_pc = recv_pc;

    uint64_t send_time = m_event_queue->time() + 1;
    uint64_t* send_data = new uint64_t;
    *send_data = recv_pc;
    this->createEvent(Event(send_time, (Agent*)m_upc, (uint8_t*)send_data, 8));
  }

};

class UpdatePC : public Agent {
private:
  PC* m_pc;

public:
  UpdatePC(EventQueue* event_queue) : Agent(event_queue), m_pc(nullptr) {}

  void connect(PC* pc) { m_pc = pc; }

  void recvEvent(uint8_t* data, uint64_t size) {
    EventEntry event = { nullptr, data, size };
    printf("[%ld] Recv Event Update PC\n", m_event_queue->time());
    uint64_t recv_pc = *(uint64_t*)data;

    uint64_t send_time = m_event_queue->time() + 1;
    uint64_t* send_data = new uint64_t;
    *send_data = recv_pc + 4;
    this->createEvent(Event(send_time, (Agent*)m_pc, (uint8_t*)send_data, 8));
  }

};

int main() {

  EventQueue event_queue = EventQueue();

  PC pc = PC(&event_queue);
  UpdatePC upc = UpdatePC(&event_queue);

  pc.connect(&upc);
  upc.connect(&pc);

  pc.init();

  event_queue.run();

  return 0;
}
