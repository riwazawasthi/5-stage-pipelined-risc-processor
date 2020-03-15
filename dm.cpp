#include "dm.h"

void dataMemory :: dataMemory_prc()
{
  if(dm_write.read()==1) //data to be written
  {
    ram[dm_addr.read()] = data_inout.read();

  }
  else if (dm_read.read()==1) //data to be read
  {
    data_inout.write(ram[dm_addr.read()]);
  }
  else
  {
    //do nothing

  }

}
