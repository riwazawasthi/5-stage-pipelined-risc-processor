#include "pm.h"

void programMemory::programMemory_prc()
{
  pm_out.write(rom[pm_in.read()]);
}
