#include "pm.h"

void programMemory::programMemory_prc()
{
  instr_out.write(rom[pm_in.read()]);
}

void programMemory::read(){
  cout<<"******************Program Memory************************"<<endl;
  for(int i =0; i<rom.size(); i++){
    cout<<std::bitset<16>(rom[i])<<endl;
  }
}

void programMemory::write(std::vector<sc_uint<16>> v){
  for (int i = 0; i<v.size(); i++){
    rom.push_back(v[i]);
  }
}
