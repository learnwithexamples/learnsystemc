// Learn with Examples, 2020, MIT license
#include <systemc>
using namespace sc_core;

SC_MODULE(MODULE_A) {
  SC_CTOR(MODULE_A) { // constructor taking only module name
    SC_METHOD(func_a); // register member function to systemC simulation kernel, to be explained later.
  }
  void func_a() { // a member function with no input, no output
    std::cout << name() << std::endl;
  }
};

SC_MODULE(MODULE_B) {
  SC_CTOR(MODULE_B) { // constructor
    SC_METHOD(func_b); // register member function
  }
  void func_b(); // declare function
};
void MODULE_B::func_b() { // define function outside class definition
  std::cout << this->name() << std::endl;
}
SC_MODULE(MODULE_C) { // constructor taking more arguments
  const int i;
  SC_CTOR(MODULE_C); // SC_HAS_PROCESS is recommended, see next example for details
  MODULE_C(sc_module_name name, int i) : sc_module(name), i(i) { // explcit constructor
    SC_METHOD(func_c);
  }
  void func_c() {
    std::cout << name() << ", i = " << i << std::endl;
  }
};

int sc_main(int, char*[]) {
  MODULE_A module_a("module_a");
  MODULE_B module_b("module_b");
  MODULE_C module_c("module_c",1);
  sc_start();
  return 0;
}

