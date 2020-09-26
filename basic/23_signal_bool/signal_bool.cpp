// Learn with Examples, 2020, MIT license
#include <systemc>
using namespace sc_core;

SC_MODULE(SIGNAL_BOOL) {
  sc_signal<bool> b;
  SC_CTOR(SIGNAL_BOOL) {
    SC_THREAD(writer);
    SC_THREAD(consumer);
    sensitive << b; // triggered by every value change
    dont_initialize();
    SC_THREAD(consumer_pos);
    sensitive << b.posedge_event(); // triggered by value change to true
    dont_initialize();
    SC_THREAD(consumer_neg);
    sensitive << b.negedge_event(); // triggered by value change to false
    dont_initialize();
  }
  void writer() {
    bool v = true;
    while (true) {
      b.write(v); // write to channel
      v = !v; // toggle value
      wait(1, SC_SEC); // write every 1 s
    }
  }
  void consumer() {
    while (true) {
      if (b.posedge()) { // if new value is true
        std::cout << sc_time_stamp() << ": consumer receives posedge, b = " << b << std::endl;
      } else { // if new value is false
        std::cout << sc_time_stamp() << ": consumer receives negedge, b = " << b << std::endl;
      }
      wait(); // wait for any value change
    }
  }
  void consumer_pos() {
    while (true) {
      std::cout << sc_time_stamp() << ": consumer_pos receives posedge, b = " << b << std::endl;
      wait(); // wait for value change to true
    }
  }
  void consumer_neg() {
    while (true) {
      std::cout << sc_time_stamp() << ": consumer_neg receives negedge, b = " << b << std::endl;
      wait(); // wait for value change to false
    }
  }
};

int sc_main(int, char*[]) {
  SIGNAL_BOOL signal_bool("signal_bool");
  sc_start(4, SC_SEC);
  return 0;
}