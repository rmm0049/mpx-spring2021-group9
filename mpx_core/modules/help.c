/**
  @file help.c
  Handles the help pages for all commands on the system
*/

#include <core/serial.h>
#include "mpx_supt.h"
#include "help.h"
#include <string.h>
#include "comhand.h"

/**
  Displays the correct help page for the given command
  @param char *msg
*/

void help(char *msg)
{
  int count = 20;

  //help page for version
  if (strncmp("help version", msg, 12) == 0)
  {
    sys_req(WRITE, COM1, "VERSION HELP PAGE\n\n", &count);
    sys_req(WRITE, COM1, "Usage: version\n\n", &count);
    sys_req(WRITE, COM1, "Description: Displays the current version of the system.\n", &count);
  }

  //help page for shutdown
  else if (strncmp("help shutdown", msg, 13) == 0)
  {
    sys_req(WRITE, COM1, "SHUTDOWN HELP PAGE\n\n", &count);
    sys_req(WRITE, COM1, "Usage: shutdown\n\n", &count);
    sys_req(WRITE, COM1, "Description: Prompts user for either Y/N to shutdown the system.\n", &count);
  }

  //help page for gettime
  else if (strncmp("help gettime", msg, 12) == 0)
  {
    sys_req(WRITE, COM1, "GETTIME HELP PAGE\n\n", &count);
    sys_req(WRITE, COM1, "Usage: gettime\n\n", &count);
    sys_req(WRITE, COM1, "Description: Displays the current time in 24hr format [hour:minute:seconds]\n", &count);
  }

  //help page for getdate
  else if (strncmp("help getdate", msg, 12) == 0)
  {
    sys_req(WRITE, COM1, "GETDATE HELP PAGE\n\n", &count);
    sys_req(WRITE, COM1, "Usage: getdate\n\n", &count);
    sys_req(WRITE, COM1, "Description: Displays the current date in the format [dayOfWeek day month year (4 digits)]\n", &count);
  }

  //help page for settime
  else if (strncmp("help settime", msg, 12) == 0)
  {
    sys_req(WRITE, COM1, "SETTIME HELP PAGE\n\n", &count);
    sys_req(WRITE, COM1, "Usage: settime hh:mm:ss\n\n", &count);
    sys_req(WRITE, COM1, "Description: Allows user to set a new time for the system.\n\n", &count);
  }

  //help page for setdate
  else if (strncmp("help setdate", msg, 12) == 0)
  {
    sys_req(WRITE, COM1, "SETDATE HELP PAGE\n\n", &count);
    sys_req(WRITE, COM1, "Usage: setdate [Day of Week (Mon, Tues, ...)] [Day] [Month (Jan, Feb, ...)] [Year (YYYY)]\n\n", &count);
    sys_req(WRITE, COM1, "Description: Allows user to set a new date for the system.\n\n", &count);
  }

  //using help without a command, displays the correct usage of help
  else
  {
    sys_req(WRITE, COM1, "help usage: help [command]\n", &count);
  }
}
