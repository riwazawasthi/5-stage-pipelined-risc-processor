#include "dm.h"

void dataMemory :: dataMemory_prc()
{
  if(dm_write.read()==1) //data to be written
  {
    if(dm_addr.read()<200){
      ram[dm_addr.read()] = data_in.read();
    }
  }
  else if (dm_read.read()==1) //data to be read
  {
    if(dm_addr.read()<200){
      data_out.write(ram[dm_addr.read()]);
    }

  }
  else
  {
    //do nothing

  }

}

void dataMemory::write(sc_uint<16> a[], int size){
  if(size>200) {size = 200;}
  for(int i=0; i<size; i++){
    ram[i] = a[i];
  }
}

void dataMemory::print(){
  cout<<"********************************Data Memory*************************************************"<<endl;
  for(int i=0; i<200; i++){
    cout<<"DM["<<i<<"]"<<" = "<<ram[i]<<endl;

  }
  cout<<"******************************Data Memory ends********************************************"<<endl;
}
