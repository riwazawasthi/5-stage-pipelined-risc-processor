#include "wb.h"

void WB:: WB_prc(){
  reg_write_out.write(reg_write.read());
  alu_result_out.write(alu_result.read());
  Rdest_out.write(Rdest.read());
  is_load_out.write(is_load.read());

}
