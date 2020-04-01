#include "processor_top.h"

void processor::pm_write_fn(std::vector<sc_uint<16>> v){
  PM->write(v);
}
void processor::pm_read_fn(){
  PM->read();
}
void processor::dm_write_fn(sc_uint<16> a[], int size){
  DM->write(a,size);
}
void processor::dm_read_fn(){
  DM->print();
}
void processor::rf_write_fn(sc_uint<16> a[], int size){
  RF->write(a,size);
}
void processor::rf_read_fn(){
  RF->print();
}
