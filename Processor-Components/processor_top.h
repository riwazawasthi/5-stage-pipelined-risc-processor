#include "systemc.h"
#include "pm.h"
#include "decode.h"
#include "rf.h"
#include "EX.h"
#include "mem.h"
#include "dm.h"
#include "wb.h"

SC_MODULE (processor){
  sc_in<bool> clk, rst;

  void pm_write_fn(std::vector<sc_uint<16>> v);
  void pm_read_fn();
  void dm_write_fn(sc_uint<16> a[], int size);
  void dm_read_fn();
  void rf_write_fn(sc_uint<16> a[], int size);
  void rf_read_fn();

  sc_signal<bool> clear_pipeline;
  sc_signal<sc_uint<16>> PC_out_mem, PC_to_reg;
  sc_signal<bool> br_taken_mem;
  sc_signal<sc_uint<16>> instruction;

  programMemory *PM;

  sc_signal<bool> c_imm, c_sub, c_carry, c_mov, c_jump, c_store, c_load_store, reg_write, dm_read, dm_write;
  sc_signal<sc_uint<8>> imm;
  sc_signal<sc_uint<4>> Rdest;
  sc_signal<sc_uint<5>> alu_op;
  sc_signal<sc_uint<16>> PC_out;
  sc_signal<sc_uint<4>> raddr1, raddr2;
  sc_signal<bool> rf_r;

  decode *Decode;

  sc_signal<sc_uint<16>> rout1, rout2;
  sc_signal<bool> reg_write_out_wb;
  sc_signal<sc_uint<4>> Rdest_out_wb;
  sc_signal<sc_uint<16>> data_out_wb;

  registerFile *RF;

  sc_signal<sc_uint<16>> alu_data;
  sc_signal<sc_uint<4>> Rdest_out;
  sc_signal<bool> br_taken_alu;
  sc_signal<sc_uint<16>> mdr;
  sc_signal<sc_uint<16>> mar;
  sc_signal<bool> reg_write_out;
  sc_signal<bool> dm_read_out, dm_write_out;
  sc_signal<sc_uint<16>> PC_alu;

  EX *Exec;

  sc_signal<sc_uint<16>> alu_result_mem;
  sc_signal<sc_uint<4>> Rdest_out_mem;
  sc_signal<bool> dm_read_out_mem, dm_write_out_mem,reg_write_out_mem, is_load;
  sc_signal<sc_uint<16>> mar_out, mdr_out;

  MEM *mem;

  sc_signal<sc_uint<16>> dm_data;

  dataMemory *DM;

  WB *wb;

  SC_CTOR(processor)
  {
    PM = new programMemory("programMemory");//PROGRAM MEMORY
    PM->instr_out(instruction);
    PM->clk(clk);
    PM->rst(rst);
    PM->PC_in(PC_out_mem);
    PM->br_taken(br_taken_mem);
    PM->PC_to_reg(PC_to_reg);
    PM->clear_pipeline(clear_pipeline);

    Decode = new decode("Decode");
    Decode->clear_pipeline(clear_pipeline);
    Decode->instruction(instruction);
    Decode->clock(clk);
    Decode->PC_in(PC_to_reg);
    Decode->c_imm(c_imm);
    Decode->c_sub(c_sub);
    Decode->c_carry(c_carry);
    Decode->c_mov(c_mov);
    Decode->c_jump(c_jump);
    Decode->c_store(c_store);
    Decode->c_load_store(c_load_store);
    Decode->reg_write(reg_write);
    Decode->dm_read(dm_read);
    Decode->dm_write(dm_write);
    Decode->imm(imm);
    Decode->Rdest(Rdest);
    Decode->alu_op(alu_op);
    Decode->PC_out(PC_out);
    Decode->raddr1(raddr1);
    Decode->raddr2(raddr2);
    Decode->rf_r(rf_r);

    RF = new registerFile("RF");
    RF->rf_r(rf_r);
    RF->rf_w(reg_write_out_wb);
    RF->raddr1(raddr1);
    RF->raddr2(raddr2);
    RF->waddr(Rdest_out_wb);
    RF->rf_in(data_out_wb);
    RF->rout1(rout1);
    RF->rout2(rout2);

    Exec = new EX("EX"); //EXECUTE
    Exec->clear_pipeline(clear_pipeline);
    Exec->clk(clk);
    Exec->c_imm(c_imm);
    Exec->c_sub(c_sub);
    Exec->c_carry(c_carry);
    Exec->c_mov(c_mov);
    Exec->c_jump(c_jump);
    Exec->c_store(c_store);
    Exec->c_load_store(c_load_store);
    Exec->reg_write(reg_write);
    Exec->dm_read(dm_read);
    Exec->dm_write(dm_write);
    Exec->imm(imm);
    Exec->Rsrc_amount_data(rout1);
    Exec->Rdest_data(rout2);
    Exec->Rdest(raddr2);
    Exec->alu_op(alu_op);
    Exec->PC_in(PC_out);
    Exec->alu_data(alu_data);
    Exec->Rdest_out(Rdest_out);
    Exec->br_taken(br_taken_alu);
    Exec->mdr(mdr);
    Exec->mar(mar);
    Exec->reg_write_out(reg_write_out);
    Exec->dm_read_out(dm_read_out);
    Exec->dm_write_out(dm_write_out);
    Exec->PC_alu(PC_alu);

    mem = new MEM("MEM");  //MEMORY
    mem->clear_pipeline(clear_pipeline);
    mem->clk(clk);
    mem->alu_result(alu_data);
    mem->PC_in(PC_alu);
    mem->mar(mar);
    mem->mdr(mdr);
    mem->dm_read(dm_read_out);
    mem->dm_write(dm_write_out);
    mem->reg_write(reg_write_out);
    mem->br_taken(br_taken_alu);
    mem->Rdest(Rdest_out);
    mem->alu_result_out(alu_result_mem);
    mem->PC_out_mem(PC_out_mem);
    mem->Rdest_out(Rdest_out_mem);
    mem->dm_read_out(dm_read_out_mem);
    mem->dm_write_out(dm_write_out_mem);
    mem->reg_write_out(reg_write_out_mem);
    mem->br_taken_mem(br_taken_mem);
    mem->is_load(is_load);
    mem->mar_out(mar_out);
    mem->mdr_out(mdr_out);

    DM = new dataMemory("dataMemory");  //DATA MEMORY
    DM->dm_read(dm_read_out_mem);
    DM->dm_write(dm_write_out_mem);
    DM->dm_addr(mar_out);
    DM->data_in(mdr_out);
    DM->data_out(dm_data);

    wb = new WB("WB"); //WRITE BACK
    wb->clear_pipeline(clear_pipeline);
    wb->clk(clk);
    wb->reg_write(reg_write_out_mem);
    wb->alu_result(alu_result_mem);
    wb->dm_data(dm_data);
    wb->Rdest(Rdest_out_mem);
    wb->is_load(is_load);
    wb->reg_write_out(reg_write_out_wb);
    wb->data_out_wb(data_out_wb);
    wb->Rdest_out(Rdest_out_wb);
  }

  ~processor(){   //deconstructor
    delete PM;
    delete RF;
    delete Decode;
    delete Exec;
    delete mem;
    delete DM;
    delete wb;
  }


};
