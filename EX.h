//------------------------------------------
// Function: Header File
// File Name: EX.h
//-------------------------------------------
#include "systemc.h"

SC_MODULE(EX)
{
/*********Control signals*********************/
  sc_in<bool> c_imm; //immediate control
  sc_in<bool> c_sub; //subtract control
  sc_in<bool> c_carry; //for carry add/subtract
  sc_in<bool> c_mov; //move control
  sc_in<bool> c_imm_shift; //immediate shift control
  sc_in<bool> c_jump; //jump control
  sc_in<bool> c_store; //store control
  sc_in<bool> c_load_store;
/**********************************************/

  sc_in<bool> sign_bit; //sign bit for immediate c_imm_shift
  sc_in<sc_uint<8>> imm; //(immHi,immLo)
  sc_in<sc_uint<16>> Rsrc_amount_data, Rdest_data;
  sc_in<sc_uint<4>> Rdest; //destination regitser address
  sc_in< sc_uint<5> > alu_op;
  sc_in<bool> C_flag_in;
  sc_in<bool> F_flag_in;
  sc_in<bool> N_flag_in;
  sc_in<bool> Z_flag_in;
  sc_in<sc_uint<16>> PC_in;

  sc_out<sc_uint<16>> alu_data;
  sc_out<sc_uint<16>> mdr;
  sc_out<sc_uint<16>> mar;
  sc_out<bool> N_flag;
  sc_out<bool> F_flag;
  sc_out<bool> C_flag;
  sc_out<bool> Z_flag;
  sc_out<sc_int<16>> PC_out;

  sc_int<16> oprnd1;
  sc_int<16> oprnd2;
  bool sub_bit;
  bool sign;
  bool carry_bit;
  sc_int<16> signextd_imm;
  

  void EX_prc();

  SC_CTOR(EX)
  {
    SC_METHOD(EX_prc);
    sensitive<<alu_op<<Rsrc_amount_data<<Rdest_data;
  }

};
