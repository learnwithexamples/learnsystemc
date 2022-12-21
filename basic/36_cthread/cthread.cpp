// Learn with Examples, 2020, MIT license
#include <systemc>
using namespace sc_core;

SC_MODULE(MODULE) {
  sc_in<bool> clk; // need event_finder method, cannot use basic sc_port
  SC_CTOR(MODULE) {
    SC_CTHREAD(cthread1, clk); // sensitive to clk pos edge
    // no static sensitivity, thus, cannot use dont_initialize()
    //SC_CTHREAD(cthread2, clk.pos()); // sensitive to clk pos edge
    SC_CTHREAD(cthread3, clk.neg()); // sensitive to clk neg edge

    SC_THREAD(cthread2);
    sensitive << clk.pos();
  }
  void cthread1() {
    while (true) {
      wait(); // wait for clk pos edge; wait() right after while loop to avoid initialization
      std::cout << sc_time_stamp() << ", cthread1, value = " << clk->read() << std::endl;
    }
  }
  void cthread2() {
    while (true) {
      wait(); // wait for clk pos edge
      std::cout << sc_time_stamp() << ", cthread2, value = " << clk->read() << std::endl;
    }
  }
  void cthread3() {
    while (true) {
      wait(); // wait for clk neg edge
      std::cout << sc_time_stamp() << ", cthread3, value = " << clk->read() << std::endl;
    }
  }
};

int sc_main(int, char*[]) {
  sc_clock clk("clk", 10, SC_SEC, 0.2, 10, SC_SEC, false); // 10s period, 2s true, 8s false, start at 10s, start at false.
  MODULE module("module"); // instantiate module
  module.clk(clk); // bind port
  sc_start(31, SC_SEC); // run simulation for 31 s
  return 0;
}
