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
    display_help(count, "version",
    "version",
    "Displays the current version of the system.");
  }

  //help page for shutdown
  else if (strncmp("help shutdown", msg, 13) == 0)
  {
    display_help(count, "shutdown",
    "shutdown",
    "Prompts user for either Y/N to shutdown the system.");
  }

  //help page for gettime
  else if (strncmp("help gettime", msg, 12) == 0)
  {
    display_help(count, "gettime",
    "gettime",
    "Displays the current time in 24hr format [hour:minute:seconds]");
  }

  //help page for getdate
  else if (strncmp("help getdate", msg, 12) == 0)
  {
    display_help(count, "getdate",
    "getdate",
    "Displays the current date in the format [dayOfWeek day month year (4 digits)]");
  }

  //help page for settime
  else if (strncmp("help settime", msg, 12) == 0)
  {
    display_help(count, "settime",
    "settime hh:mm:ss",
    "Allows user to set a new time for the system.");
  }

  //help page for setdate
  else if (strncmp("help setdate", msg, 12) == 0)
  {
    display_help(count, "setdate",
    "setdate [Day of Week (Mon, Tues, ...)] [Day] [Month (Jan, Feb, ...)] [Year (YYYY)]",
    "Allows user to set a new date for the system.");
  }

  //permanent PCB commands
  //help page for suspend
  else if (strncmp("help suspend", msg, 12) == 0)
  {
    display_help(count, "suspend",
    "suspend [name]",
    "Sets the PCB with the given name to suspended and reinserts into appropriate queue.");
  }
  //help page for resume
  else if (strncmp("help resume", msg, 11) == 0)
  {
    display_help(count, "resume",
    "resume [name]",
    "Sets the PCB with the given name to not suspended and reinserts into appropriate queue.");
  }
  //help page for set priority
  else if (strncmp("help set priority", msg, 17) == 0)
  {
    display_help(count, "set priority",
    "set priority [name] [priority]",
    "Finds the PCB with the given name and changes its priority(0-9) and reinserts into appropriate queue in the correct place.");
  }
  //help page for show ...
  else if (strncmp("help show", msg, 9) == 0)
  {
    //help page for show all
    if (strncmp("help show all", msg, 13) == 0){
      display_help(count, "show all",
      "show all",
      "Displays the following information for both ready and blocked queues: name, class, state, suspended status, and priority.");
    }
    //help page for show ready
    else if (strncmp("help show ready", msg, 15) == 0)
    {
      display_help(count, "show ready",
      "show ready",
      "Displays the following information for the ready queue: name, class, state, suspended status, and priority.");
    }
    //help page for show blocked
    else if (strncmp("help show blocked", msg, 17) == 0)
    {
      display_help(count, "show blocked",
      "show blocked",
      "Displays the following information for the blocked queue: name, class, state, suspended status, and priority.");
    }
    //help page for show
    else{
      display_help(count, "show",
      "show [name]",
      "Finds the PCB with the given name and displays the PCB's name, class, state, suspended status, and priority.");
    }
  }
  //temporary PCB commands
  //help page for createPCB
  else if (strncmp("help create PCB", msg, 15) == 0)
  {
    display_help(count, "create PCB",
    "create PCB [class] [name] [priority]",
    "Creates a new Process Control Block and inserts into appropriate queue.");
  }
  //help page for delete PCB
  else if (strncmp("help delete PCB", msg, 15) == 0)
  {
    display_help(count, "delete PCB",
    "delete PCB [name]",
    "Removes the PCB with the given name from its queue and frees all associated memory.");
  }
  //help page for block
  else if (strncmp("help block", msg, 10) == 0)
  {
    display_help(count, "block",
    "block [name]",
    "Sets the PCB with the given name to blocked and reinserts into appropriate queue.");
  }
  //help page for unblock
  else if (strncmp("help unblock", msg, 12) == 0)
  {
    display_help(count, "unblock",
    "unblock [name]",
    "Sets the PCB with the given name to unblocked and reinserts into appropriate queue.");
  }

  //help page for alarm
  else if (strncmp("help alarm", msg, 10) == 0)
  {
    display_help(count, "alarm",
    "alarm \"[message]\" hh:mm:ss",
    "Sets an alarm on the system that will display the message at or after the specified time");
  }

  //using help without a command, displays the correct usage of help
  else
  {
    sys_req(WRITE, COM1, "help usage: help [command]\n", &count);
  }
}

/**
  used in help() to print help page to terminal
  @param int count, char *name, char *usage, char *descript,
*/

void display_help(int count, char *name, char *usage, char *descript){

  sys_req(WRITE, COM1, "\x1b[32mHELP PAGE\n\x1b[36m", &count);//title
  sys_req(WRITE, COM1, name, &count);
  sys_req(WRITE, COM1, "\n\n\x1b[32mUsage: \x1b[0m", &count);
  sys_req(WRITE, COM1, usage, &count);
  sys_req(WRITE, COM1, "\n\n\x1b[32mDescription: \x1b[0m", &count);
  sys_req(WRITE, COM1, descript, &count);
  sys_req(WRITE, COM1, "\n\n", &count);

}
