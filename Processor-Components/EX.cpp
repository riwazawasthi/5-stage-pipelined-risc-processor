#include "EX.h"

void EX::EX_prc()
{
 if(!clear_pipeline.read()){
  oprnd1 = 0;
  oprnd2 = 0;
  sub_bit = 0;
  sign = 0;
  carry_bit = 0;
  sc_uint<17> result;
  sc_uint<16> temp;
  sc_uint<16> PC;
  PC = PC_in.read();
  sc_uint<16> immediate = imm.read();
  signextd_imm = (immediate & 0xFF) | ((immediate & 0x80) ? 0xFF00 : 0);

  //default outputs
  alu_data.write(0x0000);
  PC_alu.write(PC_in.read());
  br_taken.write(0);
  Rdest_out.write(Rdest.read());
  reg_write_out.write(reg_write.read());
  dm_read_out.write(dm_read.read());
  dm_write_out.write(dm_write.read());
  mdr.write(0x0000);
  mar.write(0x0000);

  if(c_imm.read()==1){ //check for immediate operations
    if(c_sub.read()==1){ //check if a subtract operation
      oprnd1 = ~signextd_imm; //one's complement

    }
    else {
      oprnd1 = signextd_imm;
    }
  }
  else{
    if(c_sub.read()==1){
      oprnd1 = ~(Rsrc_amount_data.read()); //one's complement
    }
    else{
      oprnd1 = Rsrc_amount_data.read();
    }
  }

  if(c_mov.read()==1){ //check for move  operations
    oprnd2 = 0x0000;
  }
  else{
    oprnd2 = Rdest_data.read();
  }

  if(c_imm.read()==1){ //check for shift immediate operations
    sign = imm.read().range(4,4);
  }
  else{
    sign = 0;
  }

  if(c_sub.read()==1){  //check for subtract operations
    sub_bit = 1;
  }
  else{
    sub_bit = 0;
  }

  if(c_carry.read()==1){
    carry_bit = C_flag.read();
  }
  else{
    carry_bit = 0;
  }

  switch(alu_op.read()){
    //ADD, ADDI, ADDC, ADDCI, SUB, SUBI, SUBC, SUBCI
    case 0:
    case 1:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
      result = oprnd1 + oprnd2 + sub_bit + carry_bit;
      if(oprnd1.to_int() > 0 && (oprnd2).to_int() > 0 && result.range(15,0).to_int() < 0) { //check overflow
        F_flag.write(1);
      }
      else if (oprnd1.to_int()<0 && (oprnd2).to_int()<0 && result.range(15,0).to_int()>0){
        F_flag.write(1);
      }
      else{
        F_flag.write(0);
      }

      break;

    //ADDU, ADDUI
    case 2:
    case 3:
      result = oprnd1 + oprnd2 + sub_bit + carry_bit;
      if(result & 0x10000){ //check carry
        C_flag.write(1);
      }
      else{
        C_flag.write(0);
      }

      break;

    //MUL, MULI
    case 10:
    case 11:
      result = oprnd1 * oprnd2;
      break;

    //CMP, CMPI
    case 12:
    case 13:
      result = oprnd1 + oprnd2 + sub_bit + carry_bit;
      if(result.range(15,0).to_int() == 0){
        Z_flag.write(1);
        N_flag.write(0);
      }
      else if (result.range(15,0).to_int() <0){
        N_flag.write(1);
        Z_flag.write(0);
      }
      else{
        N_flag.write(0);
        Z_flag.write(0);
      }
      break;

    //AND, ANDI
    case 14:
    case 15:
      result = oprnd1 & oprnd2;
      break;

   //OR, NOP
   case 16:

     result = oprnd1 || oprnd2;
     break;

  //ORI
  case 17:
    result = (oprnd1 & 0x00FF) || oprnd2;
    break;

  //xor
  case 18:
    result = oprnd1 ^ oprnd2;
    break;

  //XORI
  case 19:
    result = (oprnd1 & 0x00FF) ^ oprnd2;
    break;

  //MOV
  case 20:
    result = oprnd1 + oprnd2 + sub_bit + carry_bit;
    break;

  //MOVI
  case 21:
    result = (oprnd1 & 0x00FF) + oprnd2 + sub_bit + carry_bit;
    break;

  //LSH
  case 22:
    temp = oprnd2;
    if(oprnd1>=0){
      result = temp<<oprnd1;
    }
    else{
      sc_uint<16> amount = oprnd1.to_uint();
      result = temp >> amount;
    }
    break;

  //LSHI
  case 23:
    temp = oprnd2;
    if(!sign){
      result = temp<<oprnd1.range(3,0);
    }
    else{
      result = temp >> oprnd1.range(4,0).to_uint();
    }
    break;

  //ASH
  case 24:
    if(oprnd1>=0){
      result = oprnd2<<oprnd1;
    }
    else{
      sc_uint<16> amount = oprnd1.to_uint();
      result = oprnd2 >> amount;
    }
    break;

  //ASHI
  case 25:
    if(!sign){
      result = oprnd2<<oprnd1.range(3,0);
    }
    else{
      result = oprnd2 >> oprnd1.range(3,0);
    }
    break;

  //LUI
  case 26:
    result = (oprnd1 & 0x00FF) << 8;
    break;

 //LOAD
 case 27:
   result = oprnd1;
   break;

 //STOR
 case 28:
   result = oprnd1;
   break;

   //Bcond
   case 29:
     br_taken.write(1);
     if(Rdest.read() == 0){
       if(Z_flag.read()){
         PC_alu.write(PC + oprnd1);
       }
     }

     else if (Rdest.read()== 1){
       if(Z_flag.read()==0){
         PC_alu.write(PC + oprnd1);
       }
     }

     else if(Rdest.read() == 11){
       if(Z_flag.read() || N_flag.read()){
         PC_alu.write(PC + oprnd1);
       }
     }

     else if(Rdest.read() == 2){
       if(C_flag.read()){
         PC_alu.write(PC + oprnd1);
       }
     }

     else if(Rdest.read() == 3){
       if(!C_flag.read()){
         PC_alu.write(PC + oprnd1);
       }
     }

     else if(Rdest.read() == 6){
       if(N_flag.read()){
         PC_alu.write(PC + oprnd1);
       }
     }

     else if(Rdest.read() == 7){
       if(!N_flag.read()){
         PC_alu.write(PC + oprnd1);
       }
     }

     else if(Rdest.read() == 8){
       if(F_flag.read()){
         PC_alu.write(PC + oprnd1);
       }
     }

     else if(Rdest.read()==9){
       if(!F_flag.read()){
         PC_alu.write(PC + oprnd1);
       }
     }

     else if(Rdest.read()==12){
       if(!N_flag.read() && !Z_flag.read()){
         PC_alu.write(PC + oprnd1);
       }
     }

     else if(Rdest.read()==14){
       PC_alu.write(PC + oprnd1);
     }

     else{
       PC_alu.write(PC);
     }
     break;

   //Jcond
   case 30:
   br_taken.write(1);
   if(Rdest.read() == 0){
     if(Z_flag.read()){
       PC_alu.write(oprnd1/2);
     }
   }

   else if (Rdest.read()== 1){
     if(Z_flag.read()==0){
       PC_alu.write(oprnd1/2);
     }
   }

   else if(Rdest.read() == 11){
     if(Z_flag.read() || N_flag.read()){
       PC_alu.write(oprnd1/2);
     }
   }

   else if(Rdest.read() == 2){
     if(C_flag.read()){
       PC_alu.write(oprnd1/2);
     }
   }

   else if(Rdest.read() == 3){
     if(!C_flag.read()){
       PC_alu.write( oprnd1/2);
     }
   }

   else if(Rdest.read() == 6){
     if(N_flag.read()){
       PC_alu.write(oprnd1/2);
     }
   }

   else if(Rdest.read() == 7){
     if(!N_flag.read()){
       PC_alu.write(oprnd1/2);
     }
   }

   else if(Rdest.read() == 8){
     if(F_flag.read()){
       PC_alu.write(oprnd1/2);
     }
   }

   else if(Rdest.read()==9){
     if(!F_flag.read()){
       PC_alu.write(oprnd1/2);
     }
   }

   else if(Rdest.read()==12){
     if(!N_flag.read() && !Z_flag.read()){
       PC_alu.write(oprnd1/2);
     }
   }

   else if(Rdest.read()==14){
     PC_alu.write(oprnd1/2);
   }

   else{
     PC_alu.write(PC);
   }
   break;

  //JAL
  case 31:
    br_taken.write(1);
    result = PC;
    PC_alu.write(oprnd2/2);
    break;

  default:
    break;

  }
  result = result & 0x0FFFF;
  alu_data.write(result.range(15,0));
  if(c_store.read()) {mdr.write(oprnd2.to_uint());}
  if(c_load_store.read()) {mar.write((result).to_uint());}
}
else{
  alu_data.write(0x0000);
  PC_alu.write(0);
  br_taken.write(0);
  Rdest_out.write(0);
  reg_write_out.write(0);
  dm_read_out.write(0);
  dm_write_out.write(0);
  mdr.write(0x0000);
  mar.write(0x0000);
}
}
