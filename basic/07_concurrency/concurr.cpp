// Learn with Examples, 2020, MIT license
#include <systemc>
using namespace sc_core;

SC_MODULE(CONCURRENCY) {
  SC_CTOR(CONCURRENCY) { // constructor
    SC_THREAD(thread1); // register thread1
    SC_THREAD(thread2); // register thread2
  }
  void thread1() {
    while(true) { // infinite loop
      std::cout << sc_time_stamp() << ": thread1" << std::endl;
      wait(2, SC_SEC); // trigger again after 2 "simulated" seconds
    }
  }
  void thread2() {
    while(true) {
      std::cout << "\t" << sc_time_stamp() << ": thread2" << std::endl;
      wait(3, SC_SEC);
    }
  }
};

int sc_main(int, char*[]) {
  CONCURRENCY concur("concur"); // define an object
  sc_start(10, SC_SEC); // run simulation for 10 seconds
  return 0;
}
