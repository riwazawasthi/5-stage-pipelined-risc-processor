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

void registerFile::write(sc_uint<16> a[], int size){
  for(int i=0; i<size; i++){
    regdata[i] = a[i];
  }
}

void registerFile::print(){
  cout<<"********************************Register File*************************************************"<<endl;
  for(int i=0; i<16; i++){
    cout<<"R["<<i<<"]"<<" = "<<regdata[i]<<endl;
  }
}
