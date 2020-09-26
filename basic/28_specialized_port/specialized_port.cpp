// Learn with Examples, 2020, MIT license
#include <systemc>
using namespace sc_core;

SC_MODULE(WRITER) {
  sc_out<bool> p1, p2; // specialized ports
  SC_CTOR(WRITER) {
    SC_THREAD(writer);
    p1.initialize(true); // #10, initialize default value to true
  }
  void writer() {
    bool v = true;
    while (true) {
      p1->write(v); // #2 write through port
      v = !v; // value change
      wait(1, SC_SEC); // repeat after 1 s
    }
  }
};
SC_MODULE(READER) {
  sc_in<bool> p1, p2; // specialized ports
  SC_CTOR(READER) {
    SC_THREAD(reader1);
    sensitive << p1 << p2; // #3 default_event(), same as p->default_event() or p.default_event()
    dont_initialize();
    SC_THREAD(reader2);
    sensitive << p1.value_changed(); // #11, sensitive to value change event of an un-bound port
    dont_initialize();
    SC_THREAD(reader3);
    sensitive << p1.neg(); // #13, sensitive to neg event of an un-bound port
    dont_initialize();
    SC_THREAD(reader4);
    sensitive << p1.pos(); // #12, sensitive to pos event of an un-bound port
    dont_initialize();
  }
  void reader1() {
    while (true) {
      std::cout << sc_time_stamp() << ": default_event. p1 = " << p1->read() << "; p1 triggered? " << p1->event() << "; p2 triggered? " << p2->event() << std::endl; // #1 read(), #4 event()
      wait();
    }
  }
  void reader2() {
    while (true) {
      std::cout << sc_time_stamp() << ": value_changed_event. p1 = " << p1->read() <<  std::endl; // #1 read()
      wait();
    }
  }
  void reader3() {
    while (true) {
      std::cout << sc_time_stamp() << ": negedge_event. p1 = " << p1->read() << "; negedge = " << p1->negedge() << std::endl; // #8, if negedge happened
      wait();
    }
  }
  void reader4() {
    while (true) {
      std::cout << sc_time_stamp() << ": posedge_event. p1 = " << p1->read() <<  "; posedge = " << p1->posedge() << std::endl; // #6, if posedge happened
      wait();
    }
  }
};

int sc_main(int, char*[]) {
  WRITER writer("writer"); // instantiate writer
  READER reader("reader"); // instantiate reader
  sc_signal<bool> b1, b2; // declare boolean signal channel
  writer.p1(b1); // port binding
  writer.p2(b2);
  reader.p1(b1);
  reader.p2(b2);
  sc_start(4, SC_SEC);
  return 0;
}