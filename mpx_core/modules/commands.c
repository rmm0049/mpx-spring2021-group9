/**
 @file commands.c
 Contains function commands() to display the available user commands
*/

#include "commands.h"
#include <core/serial.h>
#include "mpx_supt.h"
#include <core/io.h>
#include <string.h>


/**
  Outputs the current available user commands
*/

void commands()
{
  int count = 10;

  sys_req(WRITE, COM1, "\x1b[32mAVAILABLE COMMANDS:\n", &count); //change color to green
  sys_req(WRITE, COM1, "   Time and Date\n", &count); //subsection of time and date
  sys_req(WRITE, COM1, "      gettime\n", &count);
  sys_req(WRITE, COM1, "      getdate\n", &count);
  sys_req(WRITE, COM1, "      settime\n", &count);
  sys_req(WRITE, COM1, "      setdate\n", &count);
  sys_req(WRITE, COM1, "   Current Version\n", &count); //subsection of version
  sys_req(WRITE, COM1, "      version\n", &count);
  sys_req(WRITE, COM1, "   Command Usage Help\n", &count); //subsection of help
  sys_req(WRITE, COM1, "      help\n", &count);
  sys_req(WRITE, COM1, "   Shutdown Program\n", &count); //subsection of shutdown
  sys_req(WRITE, COM1, "      shutdown\n", &count);
  sys_req(WRITE, COM1, "\x1b[0m", &count); //change color back to default
}
