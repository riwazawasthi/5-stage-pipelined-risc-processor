#include "rf.h"

int sc_main (int argc, char* argv[])
{
  sc_signal<bool> rf_r_w;
  sc_signal<sc_uint<4>> raddr1;
  sc_signal<sc_uint<4>> raddr2;
  sc_signal<sc_uint<4>> waddr;
  sc_signal<sc_uint<16>> rf_in;

  sc_signal<sc_uint<16>> rout1;
  sc_signal<sc_uint<16>> rout2;

  registerFile RF("registerFile");
  RF.rf_r_w(rf_r_w);
  RF.raddr1(raddr1);
  RF.raddr2(raddr2);
  RF.waddr(waddr);
  RF.rf_in(rf_in);
  RF.rout1(rout1);
  RF.rout2(rout2);

  sc_start(10, SC_NS);
  RF.print();
  sc_uint<16> a[16];
  a[10] = 450;
  a[2] = 448;
  a[15] = 6000;
  a[0] = 5000;
  RF.write(a,16);
  sc_start(10, SC_NS);
  RF.print();
  sc_start(10,SC_NS);

  rf_r_w.write(1);
  waddr.write(14);
  rf_in.write(8888);
  sc_start(10, SC_NS);
  RF.print();
  sc_start(10,SC_NS);

  return 0;


}
