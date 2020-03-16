#include "systemc.h"
#include "pm.h"
#include "decode.h"
#include "rf.h"
#include "EX.h"
#include "mem.h"
#include "dm.h"
#include "wb.h"

int sc_main (int argc, char* argv[])
{
  sc_signal<bool> clk, rst;

  sc_signal<sc_uint<16>> PC_out_mem, PC_to_reg;
  sc_signal<bool> br_taken_mem;
  sc_signal<sc_uint<16>> instruction;

  programMemory PM("programMemory");//PROGRAM MEMORY
  PM(instruction,clk,rst,PC_out_mem,br_taken_mem, PC_to_reg);

  sc_signal<bool> c_imm, c_sub, c_carry, c_mov, c_jump, c_store, c_load_store, reg_write, dm_read, dm_write;
  sc_signal<sc_uint<8>> imm;
  sc_signal<sc_uint<4>> Rdest;
  sc_signal<sc_uint<5>> alu_op;
  sc_signal<sc_uint<16>> PC_out;
  sc_signal<sc_uint<4>> raddr1, raddr2;
  sc_signal<bool> rf_r;

  decode Decode("decode");//DECODE
  Decode(instruction, clk, PC_to_reg, c_imm, c_sub, c_carry,
  c_mov, c_jump, c_store, c_load_store, reg_write, dm_read, dm_write,
  imm, Rdest, alu_op, PC_out, raddr1, raddr2, rf_r);


  sc_signal<sc_uint<16>> rout1, rout2;
  sc_signal<bool> reg_write_out_wb;
  sc_signal<sc_uint<4>> Rdest_out_wb;
  sc_signal<sc_uint<16>> data_out_wb;
  registerFile RF("registerFile"); //Register File
  RF(rf_r, reg_write_out_wb,raddr1, raddr2, Rdest_out_wb,data_out_wb, rout1, rout2);

  sc_signal<sc_uint<16>> alu_data;
  sc_signal<sc_uint<4>> Rdest_out;
  sc_signal<bool> br_taken_alu;
  sc_signal<sc_uint<16>> mdr;
  sc_signal<sc_uint<16>> mar;
  sc_signal<bool> reg_write_out;
  sc_signal<bool> dm_read_out, dm_write_out;
  sc_signal<sc_uint<16>> PC_alu;

  EX Exec("EX"); //EXECUTE
  Exec(clk, c_imm, c_sub, c_carry,
  c_mov, c_jump, c_store, c_load_store, reg_write, dm_read, dm_write,
  imm, rout1, rout2, raddr2, alu_op, PC_out, alu_data, Rdest_out,
  br_taken_alu, mdr, mar, reg_write_out, dm_read_out, dm_write_out, PC_alu);

  sc_signal<sc_uint<16>> alu_result_mem;
  sc_signal<sc_uint<4>> Rdest_out_mem;
  sc_signal<bool> dm_read_out_mem, dm_write_out_mem,reg_write_out_mem, is_load;
  sc_signal<sc_uint<16>> mar_out, mdr_out;

  MEM mem("MEM");  //MEMORY
  mem(clk, alu_data, PC_alu, mar, mdr, dm_read_out, dm_write_out, reg_write_out,
  br_taken_alu, Rdest_out, alu_result_mem, PC_out_mem, Rdest_out_mem,
  dm_read_out_mem, dm_write_out_mem, reg_write_out_mem, br_taken_mem, is_load,
  mar_out, mdr_out );

  sc_signal<sc_uint<16>> dm_data;

  dataMemory DM("dataMemory");  //DATA MEMORY
  DM(dm_read_out_mem, dm_write_out_mem, mar_out, mdr_out, dm_data);



  WB wb("WB"); //WRITE BACK
  wb(clk, reg_write_out_mem, alu_result_mem, dm_data, Rdest_out_mem, is_load,
  reg_write_out_wb, data_out_wb, Rdest_out_wb);


  sc_uint<16> a[16] = {0};
  a[3] = 10;
  a[5] = 12;
  a[7] = 14;
  a[8] = 12;

  RF.write(a,16);

  sc_uint<16> d[15] = {0};
  d[10] = 36;
  d[12] = 12;
  d[14] = -24;

  DM.write(d,15);

  std::vector<sc_uint<16>> v;
  v.push_back(0x4203); //load r2, r3
  v.push_back(0x0000); //nop
  v.push_back(0x4405); //load r4, r5
  v.push_back(0x0000); //nop
  v.push_back(0x5811); //addi 17,r8
  v.push_back(0x0452); //add r2, r4
  v.push_back(0x4607); //load r6, r7
  v.push_back(0x0000); //nop
  v.push_back(0x980F); //subi 15, r8
  v.push_back(0x4205); //load r2, r5
  v.push_back(0x0000); //nop
  v.push_back(0x0000); //nop;
  v.push_back(0x0258); //add r8, r2
  v.push_back(0x4843); //stor r8, r3
  v.push_back(0x0000); //nop
  v.push_back(0x4445);//stor r4, r5

  PM.write(v);

  cout<<"Initializing simulation with program 1"<<endl;

  PM.read();
  RF.print();
  DM.print();

  sc_trace_file *fp =sc_create_vcd_trace_file("Processor");

  sc_trace(fp,clk,"CLOCK");
  sc_trace(fp,rst,"reset");
  sc_trace(fp,instruction, "instruction");
  sc_trace(fp,raddr1, "Rsrc/decode");
  sc_trace(fp,Rdest, "Rdest/decode");
  sc_trace(fp,rout1, "RF_Rsrc/RF");
  sc_trace(fp,rout2, "RF_Rdest_/RF");
  sc_trace(fp,Rdest_out_wb, "Rdest/WB");
  sc_trace(fp,Rdest_out, "Rdest/EXE");
  sc_trace(fp,Rdest_out_mem, "Rdest/MEM");
  sc_trace(fp,c_load_store, "c_load_store/decode");
  sc_trace(fp,c_store, "c_store");
  sc_trace(fp,alu_data, "alu_result/exe");
  sc_trace(fp,mdr, "mdr");
  sc_trace(fp,mar, "mar");
  sc_trace(fp,reg_write_out_wb, "reg_write/WB");
  sc_trace(fp, data_out_wb, "wb_data");
  sc_trace(fp, imm, "imm/dec");
  sc_trace(fp, c_imm, "is_imm");
  sc_trace(fp, c_sub, "is_sub");


  sc_start(0, SC_NS); //Initialize simulation;

  rst.write(0);
  for(int i = 0; i<2; i++){
    clk = 0;
    sc_start(10, SC_NS);
    clk = 1;
    sc_start(10, SC_NS);
  }

  rst.write(1);
  for(int i = 0; i<25; i++){
    clk = 0;
    sc_start(10, SC_NS);
    clk = 1;
    sc_start(10, SC_NS);
  }
  cout<<"End of simulation for program 1"<<endl;
  DM.print();
  RF.print();
  sc_close_vcd_trace_file(fp);
  return 0;







}
