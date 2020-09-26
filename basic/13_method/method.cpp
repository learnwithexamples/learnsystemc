// Learn with Examples, 2020, MIT license
#include <systemc>
using namespace sc_core;

SC_MODULE(PROCESS) {
  SC_CTOR(PROCESS) { // constructor
    SC_THREAD(thread); // register a thread process
    SC_METHOD(method); // register a method process
  }
  void thread() {
    int idx = 0; // declare only once
    while (true) { // loop forever
      std::cout << "thread"<< idx++ << " @ " << sc_time_stamp() << std::endl;
      wait(1, SC_SEC); // re-trigger after 1 s
    }
  }
  void method() {
    // notice there's no while loop here
    int idx = 0; // re-declare every time method is triggered
    std::cout << "method" << idx++ << " @ " << sc_time_stamp() << std::endl;
    next_trigger(1, SC_SEC);
  }
};

int sc_main(int, char*[]) {
  PROCESS process("process");
  sc_start(4, SC_SEC);
  return 0;
}
