// Learn with Examples, 2020, MIT license
#include <systemc>
using namespace sc_core;

SC_MODULE(MULTI) {
  sc_signal<int> s1; // a single-writer signal
  sc_signal<int, SC_MANY_WRITERS> s2; // a multi-writer signal
  SC_CTOR(MULTI) {
    SC_THREAD(writer1); // writes to s1
    SC_THREAD(writer2); // writes to s1 and s2
    SC_THREAD(consumer1);
    sensitive << s1; // sensitive to s1
    dont_initialize();
    SC_THREAD(consumer2);
    sensitive << s1 << s2; // sensitive to s1 and s2
    dont_initialize();
  }
  void writer1() {
    int v = 1; // init value
    while (true) {
      s1.write(v); // write to s1
      s2.write(v); // write to s2
      std::cout << sc_time_stamp() << ": writer1 writes " << v++ << std::endl;
      wait(1, SC_SEC); // write every 1 s
    }
  }
  void writer2() {
    int v = -1; // init value
    while (true) {
      // s1.write(v); /* cannot, otherwise runtime error: (E115) sc_signal<T> cannot have more than one driver*/
      wait(SC_ZERO_TIME); // needed to offset the write time. Otherwise runtime error: conflicting write in delta cycle 0 
      s2.write(v); // write to s2
      std::cout << sc_time_stamp() << ": writer2 writes " << v-- << std::endl;
      wait(1, SC_SEC); // write every 1 s
    }
  }
  void consumer1() {
    while (true) {
      std::cout << sc_time_stamp() << ": consumer1 reads s1=" << s1.read() << "; s2=" << s2.read() << std::endl; // read s1 and s2
      wait(); // wait for s1
    }
  }
  void consumer2() {
    while (true) {
      std::cout << sc_time_stamp() << ": consumer2 reads s1=" << s1.read() << "; s2=" << s2.read() << std::endl; // read s1 and s2
      wait(); // wait for s1 or s2
    }
  }
};

int sc_main(int, char*[]) {
  MULTI consumers("consumers");
  sc_start(2, SC_SEC); // run simulation for 2 s
  return 0;
}
