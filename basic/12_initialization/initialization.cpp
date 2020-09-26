// Learn with Examples, 2020, MIT license
#include <systemc>
using namespace sc_core;

SC_MODULE(INITIALIZATION) {
  sc_event e; // event for inter-process trigger
  SC_CTOR(INITIALIZATION) {
    SC_THREAD(trigger); // no static sensitivity
    SC_THREAD(catcher_1); // no static sensitivity
    SC_THREAD(catcher_2); // no static sensitivity
    SC_THREAD(catcher_3);
    sensitive << e; // statically sensitive to e
    dont_initialize(); // don't initialize
  }
  void trigger() {
    while (true) { // e triggered at 1, 3, 5, 7 ...
      e.notify(1, SC_SEC); // notify after 1 s
      wait(2, SC_SEC); // trigger every 2 s
    }
  }
  void catcher_1() {
    while (true) {
      std::cout << sc_time_stamp() << ": catcher_1 triggered" << std::endl;
      wait(e); // dynamic sensitivity
    }
  }
  void catcher_2() {
    wait(e); // avoid initialization --- mimic systemC 1.0 behavior
    while (true) {
      std::cout << sc_time_stamp() << ": catcher_2 triggered" << std::endl;
      wait(e); // dynamic sensitivity
    }
  }
  void catcher_3() { // relies on dont_initialize() to avoid initialization
    while (true) {
      std::cout << sc_time_stamp() << ": catcher_3 triggered" << std::endl;
      wait(e); // dynamic sensitivity
    }
  }
};

int sc_main(int, char*[]) {
  INITIALIZATION init("init");
  sc_start(4, SC_SEC);
  return 0;
}

