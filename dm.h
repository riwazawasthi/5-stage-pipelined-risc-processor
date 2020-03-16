//------------------------------------------
// Function: Header File
// File Name: dm.h
//-------------------------------------------

#include "systemc.h"

SC_MODULE(dataMemory)
{
  //---------------Ports declaration-------------
        sc_in<bool>  dm_read;
        sc_in<bool>  dm_write;
        sc_in<sc_uint<16> > dm_addr; // read register address 1
        sc_in<sc_uint<16> > data_in; // data to be written to the target register

        sc_out<sc_uint<16> > data_out;

        sc_uint<16>ram[200] = {0};

        void dataMemory_prc();
        void write(sc_uint<16> a[], int size);
        void print();

        SC_CTOR (dataMemory)
        {
          SC_METHOD (dataMemory_prc);
          sensitive <<dm_read<<dm_write<<dm_addr<<data_in<<data_out;
        }
        //End of constructor


};//End of Module
