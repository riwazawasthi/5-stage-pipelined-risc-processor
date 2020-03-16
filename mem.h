#include "systemc.h"

SC_MODULE(MEM)
{
  sc_in<sc_uint<16>> alu_result;
  sc_in<sc_uint<16>> mar;
  sc_in<sc_uint<16>> mdr;
  sc_in<bool> dm_read, dm_write, reg_write;
  sc_in<sc_uint<4>> Rdest;

  sc_out<sc_uint<16>> alu_result_out;
  sc_out<sc_uint<4>> Rdest_out;
  sc_out<bool> reg_write_out;
  sc_out<bool> is_load;
  sc_out<sc_uint<16>> mar_out;
  sc_out<sc_uint<16>> mdr_out;

  void MEM_prc();

  SC_CTOR(MEM){
    SC_METHOD(MEM_prc);
    sensitive<<alu_result<<mdr<<dm_read<<dm_write<<reg_write<<Rdest;
  }
};
