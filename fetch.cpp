#include "fetch.h"

void fetch::fetch_prc(){
  if(br_taken.read()){
    PC = PC_in.read();
  }
  else{
    PC = PC+1;
  }

  PC_to_PM.write(PC.to_uint());
  sc_int<16> temp = PC +1;
  PC_to_reg.write(temp.to_uint());
}
