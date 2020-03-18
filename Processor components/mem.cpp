#include "mem.h"
void MEM:: MEM_prc(){

  if(!clear_pipeline.read()){
  is_load.write(dm_read.read());
  reg_write_out.write(reg_write.read());
  Rdest_out.write(Rdest.read());
  dm_read_out.write(dm_read.read());
  dm_write_out.write(dm_write.read());
  br_taken_mem.write(br_taken.read());
  alu_result_out.write(alu_result.read());
  PC_out_mem.write(PC_in.read());
  mar_out.write(mar.read());
  mdr_out.write(mdr.read());
}
else{
  is_load.write(0);
  reg_write_out.write(0);
  Rdest_out.write(0);
  dm_read_out.write(0);
  dm_write_out.write(0);
  br_taken_mem.write(0);
  alu_result_out.write(0);
  PC_out_mem.write(0);
  mar_out.write(0);
  mdr_out.write(0);
}
}
