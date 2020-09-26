// Learn with Examples, 2020, MIT license
#include <systemc>
using namespace sc_core;

SC_MODULE(MODULE) { // a module write to a channel
  sc_port<sc_signal<int>> p; // a port
  SC_CTOR(MODULE) {
    SC_THREAD(writer); // a writer process
  }
  void writer() {
    int v = 1;
    while (true) {
      p->write(v++); // write to channel via port
      wait(1, SC_SEC); // write every 1 s
    }
  }
};
int sc_main(int, char*[]) {
  MODULE module("module"); // instantiate module
  sc_signal<int> s; // declares signal channel
  module.p(s); // bind port to channel

  sc_trace_file* file = sc_create_vcd_trace_file("trace"); // open trace file
  sc_trace(file, s, "signal"); // trace "s" under the name of "signal"
  sc_start(5, SC_SEC); // run simulation for 5 s
  sc_close_vcd_trace_file(file); // close trace file
  return 0;
}
