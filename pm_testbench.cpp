#include "pm.h"

int sc_main (int argc, char* argv[])
{

  sc_signal<sc_uint<16>> pm_in;
  sc_signal<sc_uint<16>> instr_out;


  programMemory PM("programMemory");
  PM.pm_in(pm_in);
  PM.instr_out(instr_out);

  sc_start(10, SC_NS);
  PM.read();

  std::vector<sc_uint<16>> v;
  v.push_back(0x4382);
  v.push_back(0x0000);
  PM.write(v);
  PM.read();
  sc_start(10,SC_NS);

  return 0;


}
