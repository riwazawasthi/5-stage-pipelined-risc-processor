#include "decode.h"

void decode::decode_prc(){
 if(!clear_pipeline.read()){
  c_imm.write(1);
  c_sub.write(0);
  c_carry.write(0);
  c_mov.write(0);
  c_jump.write(0);
  c_store.write(0);
  c_load_store.write(0);
  reg_write.write(1);
  dm_read.write(0);
  dm_write.write(0);
  rf_r.write(1);
  raddr1.write(instruction.read().range(3,0));
  raddr2.write(instruction.read().range(11,8));

  imm.write(instruction.read().range(7,0));
  Rdest.write(instruction.read().range(11,8));
  PC_out.write(PC_in.read());
  alu_op.write(0);

  opc1 = instruction.read().range(15,12);
  opc2 = instruction.read().range(7,4);


  switch(opc1){

    case 0b0000:
      c_imm.write(0);
      switch(opc2){
        case 0b0101:
          alu_op.write(0);
          break;

        case 0b0110:
          alu_op.write(2);
          break;

        case 0b0111:
          alu_op.write(4);
          c_carry.write(1);
          break;

        case 0b1110:
          alu_op.write(10);
          break;

        case 0b1001:
          alu_op.write(6);
          c_sub.write(1);
          break;

       case 0b1010:
         alu_op.write(8);
         c_sub.write(1);
         c_carry.write(1);
         break;

        case 0b1011:
          alu_op.write(12);
          reg_write.write(0);
          c_sub.write(1);
          break;

        case 0b0001:
          alu_op.write(14);
          break;

        case 0b0010:
          alu_op.write(16);
          break;

        case 0b0011:
          alu_op.write(18);
          break;

        case 0b1101:
          alu_op.write(20);
          c_mov.write(1);
          break;

        default:
          reg_write.write(0);
          c_imm.write(0);

          break;

      }

      break;

    case 0b0101:
      alu_op.write(1);
      break;

    case 0b0110:
      alu_op.write(3);
      break;

    case 0b0111:
      alu_op.write(5);
      c_carry.write(1);
      break;

    case 0b1110:
      alu_op.write(11);
      break;

    case 0b1001:
      alu_op.write(7);
      c_sub.write(1);
      break;

    case 0b1010:
      alu_op.write(9);
      c_carry.write(1);
      c_sub.write(1);
      break;

    case 0b1011:
      alu_op.write(13);
      reg_write.write(0);
      c_sub.write(1);
      break;

    case 0b0001:
      alu_op.write(15);
      break;

    case 0b0010:
      alu_op.write(17);
      break;

    case 0b0011:
      alu_op.write(19);
      break;

    case 0b1101:
      alu_op.write(21);
      c_mov.write(1);
      break;

    case 0b1000:
      switch(opc2)
      {
        case 0b0100:
          alu_op.write(22);
          c_imm.write(0);
          break;

        case 0b0001:
        case 0b0000:
          alu_op.write(23);
          break;

        case 0b0110:
          alu_op.write(24);
          c_imm.write(0);
          break;

        case 0b0011:
        case 0b0010:
          alu_op.write(25);
          break;

        default:
          reg_write.write(0);
          c_imm.write(0);

          break;

      }
      break;

    case 0b1111:
      alu_op.write(26);
      break;

    case 0b0100:
       if(opc2 == 0b0000){
         alu_op.write(27);
         c_load_store.write(1);
         dm_read.write(1);
         c_imm.write(0);
        }
        else if (opc2 == 0b0100){
          alu_op.write(28);
          c_load_store.write(1);
          c_store.write(1);
          reg_write.write(0);
          dm_write.write(1);
          c_imm.write(0);
        }
        else if(opc2==0b1100){
          alu_op.write(30);
          reg_write.write(0);
          c_imm.write(0);
          c_jump.write(1);
        }
        else if(opc2==0b1000){
          alu_op.write(31);
          c_imm.write(0);
          c_jump.write(1);
        }
        else{
          reg_write.write(0);
          c_imm.write(0);
          rf_r.write(0);

        }
        break;

      case 0b1100:
        alu_op.write(29);
        reg_write.write(0);
        c_imm.write(0);
        c_jump.write(1);
        break;

      default:
        reg_write.write(0);
        c_imm.write(0);

      break;


  }
}
else{
  c_imm.write(0);
  c_sub.write(0);
  c_carry.write(0);
  c_mov.write(0);
  c_jump.write(0);
  c_store.write(0);
  c_load_store.write(0);
  reg_write.write(0);
  dm_read.write(0);
  dm_write.write(0);
  rf_r.write(0);
  raddr1.write(0x0);
  raddr2.write(0x0);
  imm.write(0x00);
  Rdest.write(0x0);
  alu_op.write(0);
  PC_out.write(0x0000);

}


}
