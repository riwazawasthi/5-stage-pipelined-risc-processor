//------------------------------------------
// Function: Header File
// File Name: EX.h
//-------------------------------------------
#include "systemc.h"

SC_MODULE(EX)
{
/*********Control signals*********************/
  sc_in<bool>clear_pipeline;
  sc_in<bool> clk;
  sc_in<bool> c_imm; //immediate control
  sc_in<bool> c_sub; //subtract control
  sc_in<bool> c_carry; //for carry add/subtract
  sc_in<bool> c_mov; //move control
  sc_in<bool> c_jump; //jump control
  sc_in<bool> c_store; //store control
  sc_in<bool> c_load_store;
  sc_in<bool> reg_write;
  sc_in<bool> dm_read, dm_write;
/**********************************************/


  sc_in<sc_uint<8>> imm; //(immHi,immLo)
  sc_in<sc_uint<16>> Rsrc_amount_data, Rdest_data;
  sc_in<sc_uint<4>> Rdest; //destination regitser address
  sc_in< sc_uint<5> > alu_op;
  sc_in<sc_uint<16>> PC_in;

  sc_out<sc_uint<16>> alu_data;
  sc_out<sc_uint<4>> Rdest_out;
  sc_out<bool> br_taken;
  sc_out<sc_uint<16>> mdr;
  sc_out<sc_uint<16>> mar;
  sc_out<bool> reg_write_out;
  sc_out<bool> dm_read_out, dm_write_out;
  sc_out<sc_uint<16>> PC_alu;

  sc_signal<bool> C_flag;
  sc_signal<bool> F_flag;
  sc_signal<bool> N_flag;
  sc_signal<bool> Z_flag;


  sc_uint<16> oprnd1;
  sc_uint<16> oprnd2;
  bool sub_bit;
  bool sign;
  bool carry_bit;
  sc_uint<16> signextd_imm;


  void EX_prc();

  SC_CTOR(EX)
  {
    SC_METHOD(EX_prc);
    sensitive<<clk.pos();

  }

};
