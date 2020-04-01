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

  processor Processor("Processor");
  Processor(clk,rst);

  sc_uint<16> a[16] = {0};
  a[1] = 1;
  a[2] = 2;
  a[3] = 3;
  a[4] = 4;
  a[5] = 5;
  a[6] = 6;
  a[7] = 7;
  a[8] = 8;
  a[10] = 26;

  Processor.rf_write_fn(a,16);



  std::vector<sc_uint<16>> v;
  v.push_back(0x0000); //nop
  v.push_back(0x0000); //nop
  v.push_back(0x0000); //nop
  v.push_back(0x0000); //nop
  v.push_back(0x0000); //nop
  v.push_back(0x0152); //add r2, r1  //program starts from address 10. array index = address/2
  v.push_back(0x0153); //add r3, r1
  v.push_back(0x0154); //add r4, r1
  v.push_back(0x0155); //add r5, r1
  v.push_back(0xB10A); //cmpi 10,r1
  v.push_back(0x41CA); //jne r10
  v.push_back(0x0156); //add r6, r1
  v.push_back(0x0157); //add r7, r1
  v.push_back(0x0158); //add r8, r1

  Processor.pm_write_fn(v);

  cout<<"*************************Initializing simulation with program 2*************************"<<endl;
  cout<<endl;
  Processor.pm_read_fn();
  cout<<endl;
  Processor.rf_read_fn();
  cout<<endl;


  sc_start(0, SC_NS); //Initialize simulation;

  rst.write(0);
  for(int i = 0; i<2; i++){
    clk = 0;
    sc_start(10, SC_NS);
    clk = 1;
    sc_start(10, SC_NS);
  }

  rst.write(1);
  for(int i = 0; i<30; i++){
    clk = 0;
    sc_start(10, SC_NS);
    clk = 1;
    sc_start(10, SC_NS);
  }
  cout<<"End of simulation for program 2"<<endl;
  cout<<endl;

  Processor.rf_read_fn();
  
  return 0;

}
