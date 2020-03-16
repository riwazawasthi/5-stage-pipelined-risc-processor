//------------------------------------------
// Function: Header File
// File Name: pm.h
//-------------------------------------------

#include "systemc.h"
#include <vector>
#include <bitset>
SC_MODULE(programMemory)
{
  sc_in<sc_uint<16>> pm_in;
  sc_out<sc_uint<16>> instr_out;

  std::vector<sc_uint<16>> rom; //read only memory; can be pre-loaded

  void programMemory_prc();
  void read();
  void write(std::vector<sc_uint<16>> v);
  SC_CTOR (programMemory)
  {
    SC_METHOD (programMemory_prc);
    sensitive << pm_in;
  }
};
