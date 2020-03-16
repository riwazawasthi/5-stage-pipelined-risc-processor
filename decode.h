#include "systemc.h"

SC_MODULE(decode)
{
  sc_in<sc_uint<16>> instruction;
  sc_in<bool> clock;
  sc_in<sc_uint<16>> PC_in;

  /*********Control signals*********************/
  sc_out<bool> c_imm; //immediate control
  sc_out<bool> c_sub; //subtract control
  sc_out<bool> c_carry; //for carry add/subtract
  sc_out<bool> c_mov; //move control
  sc_out<bool> c_jump; //jump control
  sc_out<bool> c_store; //store control
  sc_out<bool> c_load_store; //load/store Control
  sc_out<bool> reg_write;
  sc_out<bool> dm_read, dm_write;
  /*********Data*********************/

  sc_out<sc_uint<8>> imm; //(immHi,immLo)
  sc_out<sc_uint<4>> Rdest; //destination regitser address
  sc_out< sc_uint<5> > alu_op;
  sc_out<sc_uint<16>> PC_out;

  sc_out<bool> rf_r_w;
  sc_out<sc_uint<4>> waddr;
  sc_out<sc_uint<16>> rf_in;
  sc_out<sc_uint<4>> raddr1, raddr2;


  sc_uint<4> opc1, opc2;



  void decode_prc();

  SC_CTOR(decode)
  {
    SC_METHOD(decode_prc);
    sensitive<<clock.pos();
  }
};
