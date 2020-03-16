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
        sc_inout<sc_uint<16> > data_inout; // data to be written to the target register


        sc_uint<16>ram[200];

        void dataMemory_prc();

        SC_CTOR (dataMemory)
        {
          SC_METHOD (dataMemory_prc);
          sensitive <<dm_read<<dm_write<<dm_addr<<data_inout;
        }
        //End of constructor


};//End of Module
