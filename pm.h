//------------------------------------------
// Function: Header File
// File Name: pm.h
//-------------------------------------------

#include "systemc.h"
#include <vector>
#include <bitset>
SC_MODULE(programMemory)
{

  sc_out<sc_uint<16>> instr_out;
  sc_in<bool> clk;
  sc_in<bool> rst; //active low synchronous reset for pm
  sc_in<sc_uint<16>> PC_in;
  sc_in<bool> br_taken;

  sc_out<sc_uint<16>>PC_to_reg;
  sc_out<bool> clear_pipeline;
  sc_uint<16> PC;

  std::vector<sc_uint<16>> rom; //read only memory; can be pre-loaded

  void programMemory_prc();
  
  void read();
  void write(std::vector<sc_uint<16>> v);
  SC_CTOR (programMemory)
  {
    SC_METHOD (programMemory_prc);
    sensitive <<clk.pos();

  }
};
