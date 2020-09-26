// Learn with Examples, 2020, MIT license
#include <systemc>
using namespace sc_core;

SC_MODULE(CLOCK) {
  sc_port<sc_signal_in_if<bool>> clk; // a port to access clock
  SC_CTOR(CLOCK) {
    SC_THREAD(thread); // register a thread process
    sensitive << clk; // sensitive to clock
    dont_initialize();
  }
  void thread() {
    while (true) {
      std::cout << sc_time_stamp() << ", value = " << clk->read() << std::endl; // print current clock value
      wait(); // wait for next clock value change
    }
  }
};

int sc_main(int, char*[]) {
  sc_clock clk("clk", 10, SC_SEC, 0.2, 10, SC_SEC, false); // 10s period, 2s true, 8s false, start at 10s, start at false.
  CLOCK clock("clock"); // instantiate module
  clock.clk(clk); // bind port
  sc_start(31, SC_SEC); // run simulation for 31 s
  return 0;
}
