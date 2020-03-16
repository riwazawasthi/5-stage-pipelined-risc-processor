#include "rf.h"

void registerFile :: registerFile_prc()
{
  if(rf_r_w.read()==1) //data to be written
  {
    if(waddr.read()<16){
      regdata[waddr.read()] = rf_in.read();
    }


  }
    if(raddr1.read()<16){
      rout1.write(regdata[raddr1.read()]);
    }
    else{
      rout1.write(0x0000);
    }
    if(raddr1.read()<16){
      rout2.write(regdata[raddr2.read()]);
    }
    else{
      rout2.write(0x0000);
    }


}

void registerFile::write(sc_uint<16> a[], int size){
  for(int i=0; i<size; i++){
    if(size>16) {size = 16;}
    regdata[i] = a[i];
  }
}

void registerFile::print(){
  cout<<"********************************Register File*************************************************"<<endl;
  for(int i=0; i<16; i++){
    cout<<"R["<<i<<"]"<<" = "<<regdata[i]<<endl;
  }
}
