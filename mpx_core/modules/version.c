/**
  @file version.c
  Displays the version number of the mpx_core
*/

#include "version.h"
#include <core/serial.h>
#include "mpx_supt.h"

/**
  Helps display the version number of the current system.
*/
int version()
{
  int count; 
  sys_req(WRITE, COM1, VERSION, &count);
  sys_req(WRITE, COM1, "\n", &count);
  return 0;
}
