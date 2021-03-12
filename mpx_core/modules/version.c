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
  println_message("Version R4");
  return 0;
}
