// Learn with Examples, 2020, MIT license
#include <systemc>
using namespace sc_core;

SC_MODULE(MUTEX) {
  sc_mutex m;
  SC_CTOR(MUTEX) {
    SC_THREAD(thread_1);
    SC_THREAD(thread_2);
  }
  void thread_1() {
    while (true) {
      if (m.trylock() == -1) { // try to lock the mutex
        m.lock(); // failed, wait to lock
        std::cout << sc_time_stamp() << ": thread_1 obtained resource by lock()" << std::endl;
      } else { // succeeded
        std::cout << sc_time_stamp() << ": thread_1 obtained resource by trylock()" << std::endl;
      }
      wait(1, SC_SEC); // occupy mutex for 1 s
      m.unlock(); // unlock mutex
      std::cout << sc_time_stamp() << ": unlocked by thread_1" << std::endl;
      wait(SC_ZERO_TIME); // give time for the other process to lock the mutex
    }
  }
  void thread_2() {
    while (true) {
      if (m.trylock() == -1) { // try to lock the mutex
        m.lock(); // failed, wait to lock
        std::cout << sc_time_stamp() << ": thread_2 obtained resource by lock()" << std::endl;
      } else { // succeeded
        std::cout << sc_time_stamp() << ": thread_2 obtained resource by trylock()" << std::endl;
      }
      wait(1, SC_SEC); // occupy mutex for 1 s
      m.unlock(); // unlock mutex
      std::cout << sc_time_stamp() << ": unlocked by thread_2" << std::endl;
      wait(SC_ZERO_TIME); // give time for the other process to lock the mutex
    }
  }
};

int sc_main(int, char*[]) {
  MUTEX mutex("mutex");
  sc_start(4, SC_SEC);
  return 0;
}

