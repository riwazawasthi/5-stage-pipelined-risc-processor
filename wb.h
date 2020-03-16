#include "systemc.h"

SC_MODULE(WB){
  sc_in<bool> clk;
  sc_in<bool> reg_write;
  sc_in<sc_uint<16>> alu_result;
  sc_in<sc_uint<4>> Rdest;
  sc_in<bool> is_load;

  sc_out<bool> reg_write_out;
  sc_out<sc_uint<16>> alu_result_out;
  sc_out<sc_uint<4>> Rdest_out;
  sc_out<bool> is_load_out;

  void WB_prc();

  SC_CTOR(WB){
    SC_METHOD(WB_prc);
    sensitive<<clk.pos();
  }
};
