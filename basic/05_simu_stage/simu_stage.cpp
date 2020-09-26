// Learn with Examples, 2020, MIT license
#include <systemc>
using namespace sc_core;

SC_MODULE(STAGE) {
  SC_CTOR(STAGE) { // elaboration
    std::cout << sc_time_stamp() << ": Elaboration: constructor" << std::endl;
    SC_THREAD(thread); // initialization + simulation
  }
  ~STAGE() { // cleanup
    std::cout << sc_time_stamp() << ": Cleanup: desctructor" << std::endl;
  }
  void thread() {
    std::cout << sc_time_stamp() << ": Execution.initialization" << std::endl;
    int i = 0;
    while(true) {
      wait(1, SC_SEC); // advance-time
      std::cout << sc_time_stamp() << ": Execution.simulation" << std::endl; // evaluation
      if (++i >= 2) {
        sc_stop(); // stop simulation after 2 iterations
      }
    }
  }
  void before_end_of_elaboration() {
    std::cout << "before end of elaboration" << std::endl;
  }
  void end_of_elaboration() {
    std::cout << "end of elaboration" << std::endl;
  }
  void start_of_simulation() {
    std::cout << "start of simulation" << std::endl;
  }
  void end_of_simulation() {
    std::cout << "end of simulation" << std::endl;
  }
};

int sc_main(int, char*[]) {
  STAGE stage("stage"); // Elaboration
  sc_start(); // Execution till sc_stop
  return 0; // Cleanup
}