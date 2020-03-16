
#include "decode.h"

int sc_main (int argc, char* argv[])

{

           sc_signal <sc_uint<16> > instruction, PC_in;
           sc_signal<bool> c_imm, c_sub, c_carry, c_mov, c_jump, c_store, c_load_store, reg_write, dm_read, dm_write;
           sc_signal<sc_uint<8>> imm;
           sc_signal<sc_uint<4>> Rdest;
           sc_signal<sc_uint<5>> alu_op;
           sc_signal<sc_uint<16>> PC_out;
           sc_signal<sc_uint<4>> raddr1, raddr2;

           sc_clock sig_CLOCK("CLOCK",100, SC_NS);

           decode Decode("decode") ;

           Decode.instruction(instruction);
           Decode.clock(sig_CLOCK);
           Decode.PC_in(PC_in);
           Decode.c_imm(c_imm);
           Decode.c_sub(c_sub);
           Decode.c_carry(c_carry);
           Decode.c_mov(c_mov);
           Decode.c_jump(c_jump);
           Decode.c_store(c_store);
           Decode.c_load_store(c_load_store);
           Decode.reg_write(reg_write);
           Decode.dm_read(dm_read);
           Decode.dm_write(dm_write);
           Decode.imm(imm);
           Decode.Rdest(Rdest);
           Decode.alu_op(alu_op);
           Decode.PC_out(PC_out);
           Decode.raddr1(raddr1);
           Decode.raddr2(raddr2);


//-----------------for VCD files---------------------------------------------

           sc_trace_file *fp =sc_create_vcd_trace_file("Decode_testbench");

           sc_trace(fp,sig_CLOCK,"CLOCK");
           sc_trace(fp,instruction,"instruction");
           sc_trace(fp,c_imm,"c_imm");
           sc_trace(fp,reg_write,"reg_write");
           sc_trace(fp,c_sub,"c_sub");
           sc_trace(fp,c_carry,"c_carry");
           sc_trace(fp,c_mov,"c_mov");
           sc_trace(fp,c_jump,"c_jump");
           sc_trace(fp,c_store,"c_store");
           sc_trace(fp,c_load_store,"c_load_store");
           sc_trace(fp,dm_read,"dm_read");
           sc_trace(fp,dm_write,"dm_write");
           sc_trace(fp,imm,"imm");
           sc_trace(fp,Rdest,"Rdest");
           sc_trace(fp,alu_op,"alu_op");
           sc_trace(fp,PC_out,"PC_out");
           sc_trace(fp,raddr1,"raddr1");
           sc_trace(fp,raddr2,"raddr2");



//--------------------------Simulation----------------------------------------

           sc_start(100, SC_NS);

           instruction.write(0x055A); // ADD 10, 5

           sc_start(100, SC_NS);

           instruction.write(0x057A); // ADDC 10, 5

           sc_start(100, SC_NS);
           sc_start(100, SC_NS);

           instruction.write(0xA5FF);// SUBCI 255, 5

           sc_start(100, SC_NS);
           sc_start(100, SC_NS);
           sc_start(100, SC_NS);
           sc_start(100, SC_NS);
           sc_start(100, SC_NS);

           instruction.write(0x05DA); //MOV 10,5

           sc_start(100, SC_NS);

           instruction.write(0x454F); //Stor 5,15


           sc_start(100, SC_NS);

           instruction.write(0x40CA); //Jcond 10

           sc_start(100, SC_NS);

           sc_close_vcd_trace_file(fp);

           return 0 ;

}
