/*
  -----version.c------
  Displays the version number of the mpx_core
*/

#include "version.h"
#include <core/serial.h>
#include "mpx_supt.h"

int version()
{
  int count;
  sys_req(WRITE, COM1, VERSION, &count);
  sys_req(WRITE, COM1, "\n", &count);
  return 0;
}
