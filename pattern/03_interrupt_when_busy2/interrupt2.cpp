// Learn with Examples, 2020, MIT license
#include <systemc>
using namespace sc_core;
struct sc_event2 : sc_event { // first extend sc_event, to allow pause/resume
  sc_time remainningTime, doneTime;
  bool isRunning = false;
  void notify(sc_time t) {
    isRunning = true;
    remainningTime = t;
    doneTime = sc_time_stamp() + remainningTime;
    sc_event::notify(t);
  }
  void pause() {
    remainningTime = doneTime - sc_time_stamp();
    cancel();
  }
  void resume() {
    notify(remainningTime);
  }
  void abort() {
    isRunning = false;
    cancel();
  }
  operator bool() {
    return isRunning;
  }
};

SC_MODULE(AllowIntrrupt_t) {
  sc_event task, dispatchTask, interrupt;
  sc_event2 taskDone; // allow being interrupted
  int option; // different options: abort or pause/resume
  SC_HAS_PROCESS(AllowIntrrupt_t);
  AllowIntrrupt_t(sc_module_name name, int option = 0) : sc_module(name), option(option) {
    SC_THREAD(task_handler); // receive task trigger, dispatch task
    sensitive << task;
    dont_initialize();
    
    SC_THREAD(task_processor); // process task
    sensitive << dispatchTask;
    dont_initialize();

    SC_THREAD(task_done); // callback when task completes
    sensitive << taskDone;
    dont_initialize();

    SC_THREAD(interrupt_handler); // receive interrupt
    sensitive << interrupt;
    dont_initialize();
  }
  void task_handler() {
    while (true) {
      dispatchTask.notify(); // dispatch the task
      wait();
    }
  }
  void interrupt_handler() {
    while (true) {
      std::cout << name() << ": Task interrupted at " << sc_time_stamp().to_seconds() << std::endl;
      (option == 1 && taskDone) ? taskDone.pause() : taskDone.abort(); // pause if option 1 && isRunning
      interrupt_processor();
      if (option == 1 && taskDone) { // result
        taskDone.resume();
      }
      wait();
    }
  }
  void task_done() {
    while (true) {
      taskDone.isRunning = false;
      std::cout << name() << ": Task complete at " << sc_time_stamp().to_seconds() << std::endl;
      wait();
    }
  }
  virtual void task_processor() = 0;
  virtual void interrupt_processor() = 0;
};

struct MODULE2 : AllowIntrrupt_t {
  SC_HAS_PROCESS(MODULE2);
  MODULE2(sc_module_name name, int option) : AllowIntrrupt_t(name, option) {
    SC_THREAD(task_trigger);
    SC_THREAD(interrupt_trigger);
  }
  void interrupt_processor() { // interruption will consume 0.3 second
    wait(0.3, SC_SEC);
  }
  void task_processor() {
    while (true) {
      std::cout << name() << ": Task start at " << sc_time_stamp().to_seconds() << std::endl;
      taskDone.notify(sc_time(0.5, SC_SEC)); // process takes 0.5 second to finish
      wait();
    }
  }
  void task_trigger() {
    while (sc_time_stamp() < sc_time(2, SC_SEC)) { // fire trigger every second for 2 seconds
      task.notify();
      wait(1, SC_SEC);
    }
  }
  void interrupt_trigger() {
    wait(0.2, SC_SEC); // interrupt fired 0.2 sec after task is triggered
    while (sc_time_stamp() < sc_time(2, SC_SEC)) { // fire interrupt every second for 2 seconds
      interrupt.notify();
      wait(1, SC_SEC);
    }
  }
};
int sc_main(int, char*[]) {
  MODULE2 module2a("module2a", 0); // task will abort
  MODULE2 module2b("module2b", 1); // task will pause, and resume after interruption
  sc_start(); // run simulation
  return 0;
}
