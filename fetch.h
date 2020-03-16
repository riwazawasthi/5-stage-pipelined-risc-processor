#include "systemc.h"

SC_MODULE(fetch){
  sc_in<bool> clk;
  sc_in<sc_uint<16>> PC_in;
  sc_in<bool> br_taken;

  sc_out<sc_uint<16>> PC_to_PM;
  sc_out<sc_uint<16>>PC_to_reg;

  sc_int<16> PC = -1;
  void fetch_prc();

  SC_CTOR(fetch){
    SC_METHOD(fetch_prc);
    sensitive<<clk.pos();
  }


};
