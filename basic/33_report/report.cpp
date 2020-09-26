// Learn with Examples, 2020, MIT license
#include <systemc>
using namespace sc_core;

SC_MODULE(MODULE) { // a test module
  sc_port<sc_signal<int>> p; // a port
  SC_CTOR(MODULE) { // constructor
    SC_REPORT_WARNING("ctor", "register function"); // gen report to "ctor"
    SC_THREAD(writer); // a writer process
    SC_THREAD(reader); // a reader process
    sensitive << p; // sensitive to p
    dont_initialize();
  }
  void writer() {
    int v = 1;
    while (true) {
      SC_REPORT_INFO("writer", ("write " + std::to_string(v)).c_str()); // gen report to "writer"
      p->write(v++); // write to channel via port
      wait(1, SC_SEC); // write every 1 s
    }
  }
  void reader() {
    while (true) {
      SC_REPORT_INFO("reader", ("read " + std::to_string(p->read())).c_str()); // gen report to "reader"
      wait();
    }
  }
};
int sc_main(int, char*[]) {
  sc_report_handler::set_log_file_name("report.log"); // initialize report
  sc_report_handler::set_actions("writer", SC_INFO, SC_LOG); // INFO of "writer" saved in log, no display

  MODULE module("module"); // instantiate module
  sc_signal<int> s; // declares signal channel
  module.p(s); // bind port to channel

  SC_REPORT_INFO("main", "simulation starts"); // gen report to "main"
  sc_start(2, SC_SEC); // run simulation for 2 s
  SC_REPORT_INFO("main", "simulation ends"); // gen report to "main"
  return 0;
}
