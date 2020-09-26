// Learn with Examples, 2020, MIT license
#include <systemc>
#include <vector> // use c++  vector lib
using namespace sc_core;
using namespace sc_dt; // sc_logic defined here
using std::vector; // use namespace for vector

SC_MODULE(RESOLVED_SIGNAL) {
  sc_signal_resolved rv; // a resolved signal channel
  vector<sc_logic> levels; // declares a vector of possible 4-level logic values
  SC_CTOR(RESOLVED_SIGNAL) : levels(vector<sc_logic>{sc_logic_0, sc_logic_1, sc_logic_Z, sc_logic_X}){ // init vector for possible 4-level logic values
    SC_THREAD(writer1);
    SC_THREAD(writer2);
    SC_THREAD(consumer);
  }
  void writer1() {
    int idx = 0;
    while (true) {
      rv.write(levels[idx++%4]); // 0,1,Z,X, 0,1,Z,X, 0,1,Z,X, 0,1,Z,X
      wait(1, SC_SEC); // writes every 1 s
    }
  }
  void writer2() {
    int idx = 0;
    while (true) {
      rv.write(levels[(idx++/4)%4]); // 0,0,0,0, 1,1,1,1, Z,Z,Z,Z, X,X,X,X
      wait(1, SC_SEC); // writes every 1 s
    }
  }
  void consumer() {
    wait(1, SC_SEC); // delay read by 1 s
    int idx = 0;
    while (true) {
      std::cout << " " << rv.read() << " |"; // print the read value (writer1 and writer2 resolved)
      if (++idx % 4 == 0) { std::cout << std::endl; } // print a new line every 4 values
      wait(1, SC_SEC); // read every 1 s
    }
  }
};

int sc_main(int, char*[]) {
  RESOLVED_SIGNAL resolved("resolved");
  sc_start(17, SC_SEC); // runs sufficient time to test all 16 resolve combinations
  return 0;
}