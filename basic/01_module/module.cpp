// Learn with Examples, 2020, MIT license
#include <systemc>
using namespace sc_core;

SC_MODULE(MODULE_A) { // approach #1, use systemC provided SC_MODULE macro
  SC_CTOR(MODULE_A) { // default constructor
    std::cout << name() << " constructor" << std::endl; // name() returns the object name, which is provided during instantization
  }
};
struct MODULE_B : public sc_module { // approach #2, this uses c++ syntax and is more readiable
  SC_CTOR(MODULE_B) {
    std::cout << name() << " constructor" << std::endl;
  }
};
class MODULE_C : public sc_module { // approach #3, use class instead of struct
public: // have to explicitly declare constructor function as public 
  SC_CTOR(MODULE_C) {
    std::cout << name() << " constructor" << std::endl;
  }
};

int sc_main(int, char*[]) { // systemC entry point
  MODULE_A module_a("module_a"); // declare and instantiate module_a, it's common practice to assign module name == object name
  MODULE_B module_b("modb"); // declare and instantiate module_b, module name != object name
  MODULE_C module_c("module_c"); // declare and instantiate module_c
  sc_start(); // this can be skipped in this example because module instantiation happens during elaboration phase which is before sc_start
  return 0;
}