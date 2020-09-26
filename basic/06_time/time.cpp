// Learn with Examples, 2020, MIT license
#include <systemc>
using namespace sc_core;

int sc_main(int, char*[]) {
sc_core::sc_report_handler::set_actions( "/IEEE_Std_1666/deprecated",
                                           sc_core::SC_DO_NOTHING ); // suppress warning due to set_time_resolution
  sc_set_time_resolution(1, SC_FS); // deprecated function but still useful, default is 1 PS
  sc_set_default_time_unit(1, SC_SEC); // change time unit to 1 second
  std::cout << "1 SEC =     " << sc_time(1, SC_SEC).to_default_time_units() << " SEC"<< std::endl;
  std::cout << "1  MS = " << sc_time(1, SC_MS).to_default_time_units()  << " SEC"<< std::endl;
  std::cout << "1  US = " << sc_time(1, SC_US).to_default_time_units()  << " SEC"<< std::endl;
  std::cout << "1  NS = " << sc_time(1, SC_NS).to_default_time_units()  << " SEC"<< std::endl;
  std::cout << "1  PS = " << sc_time(1, SC_PS).to_default_time_units()  << " SEC"<< std::endl;
  std::cout << "1  FS = " << sc_time(1, SC_FS).to_default_time_units()  << " SEC"<< std::endl;
  sc_start(7261, SC_SEC); // run simulation for 7261 second
  double t = sc_time_stamp().to_seconds(); // get time in second
  std::cout << int(t) / 3600 << " hours, " << (int(t) % 3600) / 60 << " minutes, " << (int(t) % 60) << "seconds" << std::endl;
  return 0;
}
