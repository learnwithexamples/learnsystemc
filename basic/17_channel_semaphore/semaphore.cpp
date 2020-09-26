// Learn with Examples, 2020, MIT license
#include <systemc>
using namespace sc_core;

SC_MODULE(SEMAPHORE) {
  sc_semaphore s; // declares semaphore
  SC_CTOR(SEMAPHORE) : s(2) { // init semaphore with 2 resources
    SC_THREAD(thread_1); // register 3 threads competing for resources
    SC_THREAD(thread_2);
    SC_THREAD(thread_3);
  }
  void thread_1() {
    while (true) {
      if (s.trywait() == -1) { // try to obtain a resource
        s.wait(); // if not successful, wait till resource is available
      }
      std::cout<< sc_time_stamp() << ": locked by thread_1, value is " << s.get_value() << std::endl;
      wait(1, SC_SEC); // occupy resource for 1 s
      s.post(); // release resource
      std::cout<< sc_time_stamp() << ": unlocked by thread_1, value is " << s.get_value() << std::endl;
      wait(SC_ZERO_TIME); // give time for the other process to lock
    }
  }
  void thread_2() {
    while (true) {
      if (s.trywait() == -1) { // try to obtain a resource
        s.wait(); // if not successful, wait till resource is available
      }
      std::cout<< sc_time_stamp() << ": locked by thread_2, value is " << s.get_value() << std::endl;
      wait(1, SC_SEC); // occupy resource for 1 s
      s.post(); // release resource
      std::cout<< sc_time_stamp() << ": unlocked by thread_2, value is " << s.get_value() << std::endl;
      wait(SC_ZERO_TIME); // give time for the other process to lock
    }
  }
  void thread_3() {
    while (true) {
      if (s.trywait() == -1) { // try to obtain a resource
        s.wait(); // if not successful, wait till resource is available
      }
      std::cout<< sc_time_stamp() << ": locked by thread_3, value is " << s.get_value() << std::endl;
      wait(1, SC_SEC); // occupy resource for 1 s
      s.post(); // release resource
      std::cout<< sc_time_stamp() << ": unlocked by thread_3, value is " << s.get_value() << std::endl;
      wait(SC_ZERO_TIME); // give time for the other process to lock
    }
  }
};

int sc_main(int, char*[]) {
  SEMAPHORE semaphore("semaphore");
  sc_start(4, SC_SEC);
  return 0;
}