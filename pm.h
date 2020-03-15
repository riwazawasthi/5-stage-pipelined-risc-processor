//------------------------------------------
// Function: Header File
// File Name: pm.h
//-------------------------------------------

#include "systemc.h"

SC_MODULE(programMemory)
{
  sc_in<sc_uint<16>> pm_in;
  sc_out<sc_uint<16>> pm_out;

  sc_uint<16> rom[500]; //read only memory; can be pre-loaded

  void programMemory_prc();

  SC_CTOR (programMemory)
  {
    SC_METHOD (programMemory_prc);
    sensitive << pm_in;
  }


};
