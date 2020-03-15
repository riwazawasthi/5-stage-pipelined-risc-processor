#include "rf.h"

void registerFile :: registerFile_prc()
{
  if(rf_r_w.read()==1) //data to be written
  {
    regdata[waddr.read()] = rf_in.read();

  }
  else
  {
    rout1.write(regdata[raddr1.read()]);
    rout2.write(regdata[raddr2.read()]);
  }

}
