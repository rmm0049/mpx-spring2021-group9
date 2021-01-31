/*
    -----comhand.c-------

  Description: handles the input commands from the command line
*/

#include "comhand.h"
#include "mpx_supt.h"
#include "version.h"
#include "help.h"
#include "gettime.h"
#include <core/serial.h>
#include <string.h>

int comhandler()
{
  char cmdBuffer[BUFFER];
  int bufferSize;
  int quit = 0;
  int shutdown_flag = 0;
  int count;

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
    //shutdown command
    else if (strncmp("shutdown",cmdBuffer,8) == 0 || ( (shutdown_flag == 1) ))
    {
      //shutdown function, needs to ask for confirmation Y or N
      if (shutdown_flag == 0)
      {
        char *message = "Are you sure you want to shutdown? Y/N";
        shutdown_flag = 1;
        sys_req(WRITE, COM1, message, &count);
        sys_req(WRITE, COM1, "\n", &count);
      }
      else
      {
        if (strncmp("Y", cmdBuffer,1) == 0) // if Y then quit command handler
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
      gettime();
    }
    //date commands
    else if (0)
    {

    }

    //user just presses enter, doesn't enter anything
    else if (strncmp("\r",cmdBuffer,1) == 0) {} //do nothing

    //command not recognized
    else
    {
      char *error = "Command not recognized";
      sys_req(WRITE, COM1, error, &count);
      sys_req(WRITE, COM1, "\n", &count);
    }

  }

  return 0;
}
