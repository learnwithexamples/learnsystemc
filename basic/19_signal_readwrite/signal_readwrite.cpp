// Learn with Examples, 2020, MIT license
#include <systemc>
using namespace sc_core;

SC_MODULE(SIGNAL) {
  sc_signal<int> s;
  SC_CTOR(SIGNAL) {
    SC_THREAD(readwrite);
  }
  void readwrite() {
    s.write(3);
    std::cout << "s = " << s << "; " << s.read() << std::endl;
    wait(SC_ZERO_TIME);
    std::cout << "after delta_cycle, s = " << s << std::endl;
    
    s = 4;
    s = 5;
    int tmp = s;
    std::cout << "s = " << tmp << std::endl;
    wait(SC_ZERO_TIME);
    std::cout << "after delta_cycle, s = " << s.read() << std::endl;
  }
};

int sc_main(int, char*[]) {
  SIGNAL signal("signal");
  signal.s = -1;
  sc_start();
  return 0;
}