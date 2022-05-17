// Learn with Examples, 2020, MIT license
#include <systemc>
#include <deque>
using namespace sc_core;

SC_MODULE(MODULE) {
  sc_event trigger, dispatchTask;
  std::deque<bool> bufferedEvent; // can use other types to store states needed for the task processor
  SC_CTOR(MODULE) {
    SC_THREAD(task_trigger);
    SC_THREAD(trigger_handler);
    sensitive << trigger;
    dont_initialize();
    SC_THREAD(task_processor);
    sensitive << dispatchTask;
    dont_initialize();
  }
  void task_trigger() {
    while (sc_time_stamp() < sc_time(5, SC_SEC)) { // fire trigger even second for 5 seconds
      trigger.notify();
      std::cout << "Trigger task at " << sc_time_stamp().to_seconds() << std::endl;
      wait(1, SC_SEC);
    }
  }
  void trigger_handler() {
    while (true) {
      bufferedEvent.push_back(true); // buffer the trigger
      dispatchTask.notify(); // dispatch the task
      wait();
    }
  }
  void task_processor() {
    while (true) {
      while (!bufferedEvent.empty()) { // continue process while there are buffered events
        bufferedEvent.pop_front();
        std::cout << "Process task at " << sc_time_stamp().to_seconds() << std::endl;
        wait(1.3, SC_SEC); // takes 1.3 second to process each trigger
      }
      wait();
    }
  }
};

int sc_main(int, char*[]) {
  MODULE module("module"); // instantiate module
  sc_start(); // run simulation
  return 0;
}
