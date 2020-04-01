//------------------------------------------
// Function: Header File
// File Name: rf.h
//-------------------------------------------

#include "systemc.h"

SC_MODULE(registerFile)
{
  //---------------Ports declaration-------------
        sc_in<bool>  rf_r, rf_w;
        sc_in<sc_uint<4> > raddr1; // read register address 1
        sc_in<sc_uint<4> > raddr2; // read register address 2
        sc_in<sc_uint<4> > waddr; // write register address
        sc_in<sc_uint<16> > rf_in; // data to be written to the target register

        sc_out<sc_uint<16> > rout1; // output data 1
        sc_out<sc_uint<16> > rout2; // output data 2

        sc_uint<16>regdata[16] = {0};

        void read_reg();
        void write_reg();
        void write(sc_uint<16> a[], int size);
        void print();
        SC_CTOR (registerFile)
        {
          SC_METHOD (read_reg);
          sensitive <<rf_r<<raddr1<<raddr2;

          SC_METHOD (write_reg);
          sensitive <<rf_w<<waddr<<rf_in;

        }
        //End of constructor


};//End of Module
