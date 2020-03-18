#include "dm.h"

int sc_main (int argc, char* argv[])
{
  sc_signal<bool> dm_read, dm_write;
  sc_signal<sc_uint<16>> dm_addr, data_inout;

  dataMemory DM("dataMemory");
  DM.dm_read(dm_read);
  DM.dm_write(dm_write);
  DM.dm_addr(dm_addr);
  DM.data_inout(data_inout);

  sc_start(10, SC_NS);
  DM.print();
  sc_uint<16> a[450];
  a[10] = 450;
  a[2] = 448;
  a[15] = 6000;
  a[0] = 5000;
  a[199] = 8000;
  DM.write(a,450);
  sc_start(10, SC_NS);
  DM.print();
  sc_start(10,SC_NS);

  dm_write.write(1);
  dm_addr.write(197);
  data_inout.write(8888);
  sc_start(10, SC_NS);
  DM.print();
  sc_start(10,SC_NS);

  return 0;


}
