#include "fetch.h"

void fetch::fetch_prc(){
  if(br_taken.read()){
    PC = PC_in.read();
  }
  else{
    PC = PC + 1;
  }
  PC_out.write(PC);
}
