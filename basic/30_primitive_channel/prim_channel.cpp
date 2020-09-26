// Learn with Examples, 2020, MIT license
#include <systemc>
#include <string>
using namespace sc_core;

class GENERATOR_IF : public sc_interface { // interface for interrupt generator
public:
  virtual void notify() = 0;
};
class RECEIVER_IF : public sc_interface { // interface for interrupt receiver
public:
  virtual const sc_event& default_event() const = 0; // needed for sensitive
};
class INTERRUPT : public sc_prim_channel, public GENERATOR_IF, public RECEIVER_IF { // interrupt class
public:
  INTERRUPT(sc_module_name name) : sc_prim_channel(name) {} // constructor, construct sc_prim_channel
  void notify() { // implement GENERATOR_IF
    e.notify();
  }
  const sc_event& default_event() const { // implement RECEIVER_IF
    return e;
  }
private:
  sc_event e; // private event for synchronization
};
SC_MODULE(GENERATOR) { // interrupt generator class
  sc_port<GENERATOR_IF> p; // port to generate interrupt
  SC_CTOR(GENERATOR) { // constructor
    SC_THREAD(gen_interrupt);
  }
  void gen_interrupt() {
    while (true) {
      p->notify(); // calls notify function of the INTERRUPT channel
      wait(1, SC_SEC);
    }
  }
};
SC_MODULE(RECEIVER) { // interrupt receiver class
  sc_port<RECEIVER_IF> p; // port to receive interrupt
  SC_CTOR(RECEIVER) { // constructor
    SC_THREAD(rcv_interrupt);
    sensitive << p; // monitors interrupt on port p
    dont_initialize();
  }
  void rcv_interrupt() { // triggered upon interrupt
    while (true) {
      std::cout << sc_time_stamp() << ": interrupt received" << std::endl;
      wait();
    }
  }
};

int sc_main(int, char*[]) {
  GENERATOR generator("generator"); // instantiate generator
  RECEIVER receiver("receiver"); // instantiate receiver
  INTERRUPT interrupt("interrupt"); // instantiate interrupt
  generator.p(interrupt); // port binding
  receiver.p(interrupt); // port binding
  sc_start(2, SC_SEC);
  return 0;
}
