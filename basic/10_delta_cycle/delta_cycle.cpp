// Learn with Examples, 2020, MIT license
#include <systemc>
using namespace sc_core;

SC_MODULE(DELTA) {
  int x = 1, y = 1; // defines two member variables
  SC_CTOR(DELTA) {
    SC_THREAD(add_x); // x += 2
    SC_THREAD(multiply_x); // x *= 3
    SC_THREAD(add_y); // y += 2
    SC_THREAD(multiply_y); // y *= 3
  }
  void add_x() { // x += 2 happens first
    std::cout << "add_x: " << x << " + 2" << " = ";
    x += 2;
    std::cout << x << std::endl;
  }
  void multiply_x() { // x *= 3 happens after a delta cycle
    wait(SC_ZERO_TIME);
    std::cout << "multiply_x: " << x << " * 3" << " = ";
    x *= 3;
    std::cout << x << std::endl;
  }
  void add_y() { // y += 2 happens after a delta cycle
    wait(SC_ZERO_TIME);
    std::cout << "add_y: " << y << " + 2" << " = ";
    y += 2;
    std::cout << y << std::endl;
  }
  void multiply_y() { // y *=3 happens first
    std::cout << "multiply_y: " << y << " * 3" << " = ";
    y *= 3;
    std::cout << y << std::endl;
  }
};

int sc_main(int, char*[]) {
  DELTA delta("delta");
  sc_start();
  return 0;
}

