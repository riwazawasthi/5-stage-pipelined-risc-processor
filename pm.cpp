#include "pm.h"

void programMemory::programMemory_prc()
{
  if(pm_in.read()<rom.size()){
    instr_out.write(rom[pm_in.read()]);
  }
  else{
    instr_out.write(0x0000);
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
