#include "pm.h"

int sc_main (int argc, char* argv[])
{

  sc_signal<sc_uint<16>> pm_in;
  sc_signal<sc_uint<16>> instr_out,PC_to_reg;
  sc_signal<bool> clk, br_taken, rst;

  programMemory PM("programMemory");
  PM.PC_in(pm_in);
  PM.clk(clk);
  PM.rst(rst);
  PM.br_taken(br_taken);
  PM.instr_out(instr_out);
  PM.PC_to_reg(PC_to_reg);

  PM.read();

  std::vector<sc_uint<16>> v;
  v.push_back(0x4382);
  v.push_back(0x0000);
  PM.write(v);
  PM.read();

  sc_start(0, SC_NS);
  sc_trace_file *fp =sc_create_vcd_trace_file("programMemory");

  sc_trace(fp,clk,"CLOCK");
  sc_trace(fp,instr_out, "instruction");
  sc_trace(fp,PC_to_reg, "PC_out");
  sc_trace(fp, br_taken, "br_taken");
  sc_trace(fp,pm_in, "PC_in");
  sc_trace(fp, rst, "reset");


  rst.write(0);
  for(int i = 0; i<2; i++){
    clk = 0;
    sc_start(10, SC_NS);
    clk = 1;
    sc_start(10, SC_NS);
  }
  rst.write(1);
  for(int i = 0; i<10; i++){
    clk = 0;
    sc_start(10, SC_NS);
    clk = 1;
    sc_start(10, SC_NS);
  }
  sc_close_vcd_trace_file(fp);

  return 0;


}
