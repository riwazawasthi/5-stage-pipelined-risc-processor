#include "wb.h"

void WB:: WB_prc(){
  reg_write_out.write(reg_write.read());
  if(is_load.read()){
    data_out_wb.write(dm_data.read());
  }
  else{
    data_out_wb.write(alu_result.read());
  }

  Rdest_out.write(Rdest.read());


}
