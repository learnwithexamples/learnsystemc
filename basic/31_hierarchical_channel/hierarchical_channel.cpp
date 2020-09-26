// Learn with Examples, 2020, MIT license
#include <systemc>
using namespace sc_core;

// this is a simple implementation as compared to sc_signal, just to illustrate the concept of a hieracical channel
class SIGNAL : public sc_channel, public sc_signal_inout_if<int> { // declares SIGNAL channel, inherits from sc_chanel and signal_inout_if<int>
public:
  SC_HAS_PROCESS(SIGNAL);
  SIGNAL(sc_module_name name = sc_gen_unique_name("SIG")) : sc_channel(name) {} // constructor, construct base class
  void write(const int& v) { // implements write method
    if (v != m_val) { // update only if value is new
      m_val = v; // update value
      e.notify(); // trigger event
    }
  }
  const int& read() const {
    return m_val;
  }
  const sc_event& value_changed_event() const {
    return e; // return reference to the event
  }
  const sc_event& default_event() const {
    return value_changed_event(); // allows used in static sensitivity list
  }
  const int& get_data_ref() const {
    return m_val;
  }
  bool event() const {
    return true; // dummy implementation, always return true
  }
private:
  int m_val = 0;
  sc_event e;
};

SC_MODULE(TEST) { // a test class
  SIGNAL s; // declares SIGNAL channel
  SC_CTOR(TEST) { // no name provided to s, use default
    SC_THREAD(writer); // register a writer process
    SC_THREAD(reader); // register a reader process
    sensitive << s; // use SIGNAL channel in static sensitivity list
    dont_initialize();
  }
  void writer() {
    int v = 1;
    while (true) {
      s.write(v++); // write to channel
      wait(1, SC_SEC);
    }
  }
  void reader() {
    while (true) {
      std::cout << sc_time_stamp() << ": val = " << s.read() << std::endl; // read from channel
      wait();
    }
  }
};
int sc_main(int, char*[]) {
  TEST test("test"); // instantiate generator
  sc_start(2, SC_SEC);
  return 0;
}
