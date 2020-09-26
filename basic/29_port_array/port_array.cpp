// Learn with Examples, 2020, MIT license
#include <systemc>
#include <vector> // used to define a vector of ports
using namespace sc_core;

SC_MODULE(WRITER) {
  sc_port<sc_signal_out_if<int>> p1; // #1: exactly 1 channel
  sc_port<sc_signal_out_if<int>, 0> p2; // #2: 1 or more channels, no upper limit
  sc_port<sc_signal_out_if<int>, 3> p3; // #3: 1, 2, or 3 channels
  sc_port<sc_signal_out_if<int>, 0, SC_ZERO_OR_MORE_BOUND> p4; // #4: 0 or more channels, no upper limit
  sc_port<sc_signal_out_if<int>, 1, SC_ZERO_OR_MORE_BOUND> p5; // #5: 0 or 1 channels
  sc_port<sc_signal_out_if<int>, 3, SC_ZERO_OR_MORE_BOUND> p6; // #6: 0, 1, 2, or 3 channels
  sc_port<sc_signal_out_if<int>, 3, SC_ALL_BOUND> p7; // #7: exactly 3 channels
  std::vector<sc_port<sc_signal_out_if<int>>> p9; // #9: vector of port
  SC_CTOR(WRITER) : p9(3) { // init p9 to size of 3
    SC_THREAD(writer);
  }
  void writer() {
    int v = 1;
    while (true) {
      p9[0]->write(v); // write to p9[0]
      p7[1]->write(v++); // write to p7[1]
      wait(1, SC_SEC);
    }
  }
};
SC_MODULE(READER) {
  sc_port<sc_signal_in_if<int>> p1; // #1: exactly 1 channel
  sc_port<sc_signal_in_if<int>, 0> p2; // #2: 1 or more channels, no upper limit
  sc_port<sc_signal_in_if<int>, 3> p3; // #3: 1, 2, or 3 channels
  sc_port<sc_signal_in_if<int>, 0, SC_ZERO_OR_MORE_BOUND> p4; // #4: 0 or more channels, no upper limit
  sc_port<sc_signal_in_if<int>, 1, SC_ZERO_OR_MORE_BOUND> p5; // #5: 0 or 1 channels
  sc_port<sc_signal_in_if<int>, 3, SC_ZERO_OR_MORE_BOUND> p6; // #6: 0, 1, 2, or 3 channels
  sc_port<sc_signal_in_if<int>, 3, SC_ALL_BOUND> p7; // #7: exactly 3 channels
  std::vector<sc_port<sc_signal_in_if<int>>> p9; // #9: exactly 3 channels
  SC_CTOR(READER) : p9(3) { // init p9 to size of 3
    SC_THREAD(reader7);
    sensitive << p7; // sensitive to any element of port array p7
    dont_initialize();
    SC_THREAD(reader9);
    sensitive << p9[0] << p9[1] << p9[2]; // sensitive to any element of port array p9
    dont_initialize();
  }
  void reader7() {
    while (true) {
      std::cout << sc_time_stamp() << "; reader7, port 0/1/2 = " << p7[0]->read() << "/" << p7[1]->read() << "/" << p7[2]->read() << std::endl;
      wait();
    }
  }
  void reader9() {
    while (true) {
      std::cout << sc_time_stamp() << "; reader9, port 0/1/2 = " << p9[0]->read() << "/" << p9[1]->read() << "/" << p9[2]->read() << std::endl;
      wait();
    }
  }
};

int sc_main(int, char*[]) {
  WRITER writer("writer"); // instantiate writer
  READER reader("reader"); // instantiate reader
  // declare channels
  sc_signal<int> s1; // 1 channel
  std::vector<sc_signal<int>> s2(10); // 10 channels
  std::vector<sc_signal<int>> s3(2); // 2 channel
  // leave s4 un-bound
  sc_signal<int> s5; // 1 channel
  std::vector<sc_signal<int>> s6(2); // 2 channels
  std::vector<sc_signal<int>> s7(3); // 3 channels
  // #8 is same as #9, omitted
  std::vector<sc_signal<int>> s9(3); // 3 channels
  // bind ports
  writer.p1(s1); // #1
  reader.p1(s1); // #1
  for (unsigned int i = 0; i < s2.size(); ++i) { // #2
    writer.p2(s2[i]);
    reader.p2(s2[i]);
  }
  for (unsigned int i = 0; i < s3.size(); ++i) { // #3
    writer.p3(s3[i]);
    reader.p3(s3[i]);
  }
  // s4 un-bound
  writer.p5(s5); // #5
  reader.p5(s5); // #5
  for (unsigned int i = 0; i < s6.size(); ++i) { // #6
    writer.p6(s6[i]);
    reader.p6(s6[i]);
  }
  for (unsigned int i = 0; i < s7.size(); ++i) { // #7
    writer.p7(s7[i]);
    reader.p7(s7[i]);
  }
  for (unsigned int i = 0; i < s9.size(); ++i) { // #9
    writer.p9[i](s9[i]);
    reader.p9[i](s9[i]);
  }
  sc_start(2, SC_SEC);
  return 0;
}
