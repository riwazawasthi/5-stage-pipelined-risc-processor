#include "systemc.h"
#include "processor_top.h"


int sc_main (int argc, char* argv[])
{
  sc_signal<bool> clk, rst;

  processor Processor("Processor");
  Processor(clk,rst);

  sc_uint<16> a[16] = {0};
  a[3] = 10;
  a[5] = 12;
  a[7] = 14;
  a[8] = 12;

  Processor.rf_write_fn(a,16);

  sc_uint<16> d[15] = {0};
  d[10] = 36;
  d[12] = 12;
  d[14] = -24;

  Processor.dm_write_fn(d,15);

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

  Processor.pm_write_fn(v);

  cout<<"Initializing simulation with program 1"<<endl;

  Processor.pm_read_fn();
  Processor.dm_read_fn();
  Processor.rf_read_fn();

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

  Processor.dm_read_fn();
  Processor.rf_read_fn();

  return 0;







}
