#include "mem.h"
void MEM:: MEM_prc(){

  is_load.write(dm_read.read());
  reg_write_out.write(reg_write.read());
  Rdest_out.write(Rdest.read());
  alu_result_out.write(alu_result.read());
  mar_out.write(mar.read());
  mdr_out.write(mdr.read());

}
