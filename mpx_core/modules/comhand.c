/**
  @file comhand.c

  handles the input commands from the command line
*/

#include "comhand.h"
#include "mpx_supt.h"
#include "version.h"
#include "help.h"
#include "gettime.h"
#include "getdate.h"
#include "settime.h"
#include "setdate.h"
#include "commands.h"
#include "temp_func.h"
#include "queue.h"
#include <core/serial.h>
#include <string.h>

/**
  Calls the polling function in serial.c and interprets the
  commands given to it

*/


int comhandler()
{
  char cmdBuffer[BUFFER];
  int bufferSize;
  int quit = 0;
  int shutdown_flag = 0;
  int count;

  sys_req(WRITE, COM1, "\n\x1b[32mFor a list of commands, type \x1b[0mcommands\n", &count);

  while (!quit)
  {
    memset(cmdBuffer, '\0', 100);
    bufferSize = 99;
    sys_req(READ, COM1, cmdBuffer, &bufferSize);

    /*
      Commands for R1
      version, help, shutdown, getdate, setdate, gettime, settime
    */

    //version command
    if (strncmp("version",cmdBuffer,7) == 0)
    {
      version();
    }
    //commands command
    else if (strncmp("commands",cmdBuffer,8) == 0)
    {
      commands();
    }
    //shutdown command
    else if ((strncmp("shutdown",cmdBuffer,8) == 0) || (shutdown_flag == 1))
    {
      int i;
      int valid = 1; //make sure valid command
      for (i = 9; i < strlen(cmdBuffer); i++) //checks for whitespace
      {
        if (cmdBuffer[i] == '\0' || isspace(&cmdBuffer[i])); //can be space or null character
        else{
          println_error("COMMAND NOT RECOGNIZED");
          valid = 0;
          break;
        }
      }
      if (!valid) //if not valid command continue back at top of while loop
        continue;

      //shutdown function, needs to ask for confirmation Y or N
      if (shutdown_flag == 0)
      {
        println_warning("Are you sure you want to shutdown? Y/N");
        shutdown_flag = 1;

      }
      else
      {
        if (strncmp("Y", cmdBuffer,1) == 0 || strncmp("y", cmdBuffer,1) == 0) // if Y then quit command handler
        {
          quit = 1;
        }
        else // if not shutdown, reset the shutdown flag back to 0
        {
          shutdown_flag = 0;
        }
      }

    }
    //help command
    else if (strncmp("help", cmdBuffer, 4) == 0)
    {
      help(cmdBuffer);
    }
    //time commands
    else if (strncmp("gettime", cmdBuffer, 7) == 0)
    {
      int valid = 1; //make sure valid command
      int i;
      for (i = 8; i < strlen(cmdBuffer); i++) //checks for whitespace
      {
        if (cmdBuffer[i] == '\0' || isspace(&cmdBuffer[i])); //can be space or null character
        else{
          sys_req(WRITE, COM1, "Command not recognized", &count);
          sys_req(WRITE, COM1, "\n", &count);
          valid = 0;
          break;
        }
      }
      if (!valid) //if not valid command continue back at top of while loop
        continue;

      gettime();
    }

    //settime command
    else if (strncmp("settime", cmdBuffer, 7) == 0)
    {
      settime(cmdBuffer);
    }

    //date commands
    else if (strncmp("getdate", cmdBuffer, 7) == 0)
    {
      int valid = 1; //make sure valid command
      int i;
      for (i = 8; i < strlen(cmdBuffer); i++) //checks for whitespace
      {
        if (cmdBuffer[i] == '\0' || isspace(&cmdBuffer[i])); //can be space or null character
        else{
          println_error("Command not recognized");
          valid = 0;
          break;
        }
      }
      if (!valid) //if not valid command continue back at top of while loop
        continue;

      getdate();
    }

    //setdate command
    else if (strncmp("setdate", cmdBuffer, 7) == 0)
    {
      setdate(cmdBuffer);
    }

    //temprorary PCB commands
    else if (strncmp("create PCB", cmdBuffer, 10) == 0)
    {
      createPCB(cmdBuffer);
    }
    else if (strncmp("delete PCB", cmdBuffer, 10) == 0)
    {
      deletePCB(cmdBuffer);
    }
    else if (strncmp("block PCB", cmdBuffer, 9) == 0)
    {
      blockPCB(cmdBuffer);
    }
    else if (strncmp("unblock", cmdBuffer, 7) == 0)
    {
        //unblockPCB(cmdBuffer);
    }

    //user just presses enter, doesn't enter anything
    else if (strncmp("\r",cmdBuffer,1) == 0) {} //do nothing

    //command not recognized
    else
    {
      println_error("Command not recognized");

    }

  }


  return 0;
}
