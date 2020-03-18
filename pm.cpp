#include "pm.h"

void programMemory::programMemory_prc()
{
if(rst.read()&& !br_taken.read()){
  if(PC<rom.size()){
     instr_out.write(rom[PC]);
     PC=PC+1;
   }
   else{
     instr_out.write(0x0000);
   }

   PC_to_reg.write(PC);
   clear_pipeline.write(0);
}
else if(br_taken.read()){
  clear_pipeline.write(1);
  PC = PC_in.read();
  PC_to_reg.write(0x0000);
  instr_out.write(0x0000);

}
 else{
   PC_to_reg.write(0x0000);
   PC = 0x0000;
   instr_out.write(0x0000);
   clear_pipeline.write(0);
 }
}



void programMemory::read(){
  cout<<"******************Program Memory************************"<<endl;
  if(rom.size() == 0){
    cout<<"------------------Empty---------------------------------"<<endl;
  }
  else{
    for(int i =0; i<rom.size(); i++){
      cout<<"PM["<<i<<"]"<<" = "<<std::bitset<16>(rom[i])<<endl;
    }
  }

}

void programMemory::write(std::vector<sc_uint<16>> v){
  for (int i = 0; i<v.size(); i++){
    rom.push_back(v[i]);
  }
}
