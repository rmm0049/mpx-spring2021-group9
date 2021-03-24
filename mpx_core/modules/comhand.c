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
#include "pcb_func.h"
#include "perm_pcb_comm.h"
#include "loadr3.h"
#include "alarm.h"
#include "alarmList.h"
#include "loadcomhand.h"
#include "memComm.h"
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
    if (strncmp("version", cmdBuffer, 7) == 0)
    {
      version();
    }
    //commands command
    else if (strncmp("commands", cmdBuffer, 8) == 0)
    {
      commands();
    }
    else if (strncmp("clear", cmdBuffer, 5) == 0)
    {
      simple_print("\x1b[2J");
      simple_print("\x1b[0;0f");
    }
    //shutdown command
    else if ((strncmp("shutdown", cmdBuffer, 8) == 0) || (shutdown_flag == 1))
    {
      int i;
      int valid = 1;                          //make sure valid command
      for (i = 9; i < strlen(cmdBuffer); i++) //checks for whitespace
      {
        if (cmdBuffer[i] == '\0' || isspace(&cmdBuffer[i]))
          ; //can be space or null character
        else
        {
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
        if (strncmp("Y", cmdBuffer, 1) == 0 || strncmp("y", cmdBuffer, 1) == 0) // if Y then quit command handler
        {
          if (findPCB("infinite") != NULL)
          {
            println_error("infinite process still running!");
          }
          else
          {
            quit = 1;
            deletePCB("idle");
            if (findPCB("alarm") != NULL)
              deletePCB("alarm");
            sys_req(EXIT, COM1, NULL, NULL);
          }
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
        if (cmdBuffer[i] == '\0' || isspace(&cmdBuffer[i]))
          ; //can be space or null character
        else
        {
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
        if (cmdBuffer[i] == '\0' || isspace(&cmdBuffer[i]))
          ; //can be space or null character
        else
        {
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
    else if (strncmp("delete PCB idle", cmdBuffer, 15) == 0)
    {
      println_error("Can't manipulate system process!");
    }
    else if (strncmp("delete PCB", cmdBuffer, 10) == 0)
    {
      char *delete = strtok(cmdBuffer, " ");
      delete = strtok(NULL, " ");
      delete = strtok(NULL, " ");
      deletePCB(delete);
    }

    else if (strncmp("isEmpty", cmdBuffer, 7) == 0)
    {
      isEmptyComm();
    }
    // else if (strncmp("allocate", cmdBuffer, 8) == 0)
    // {
    //   if (!getMemModule())
    //     break;
    //   char *temp = strtok(cmdBuffer, " ");
    //   temp = strtok(NULL, " ");
    //   allocateMem(atoi(temp));
    // }
    // else if (strncmp("free", cmdBuffer, 4) == 0)
    // {
    //   if (!getMemModule())
    //     break;
    //   char *temp = strtok(cmdBuffer, " ");
    //   temp = strtok(NULL, " ");
    //   freeMem(temp);
    // }

    else if (strncmp("show free", cmdBuffer, 9) == 0)
    {
      showFree();
    }
    else if (strncmp("show allocated", cmdBuffer, 14) == 0)
    {
      showAllocated();
    }
    //permanent PCB commands
    else if (strncmp("show ready", cmdBuffer, 10) == 0)
    {
      showReadyPCB();
    }
    else if (strncmp("show blocked", cmdBuffer, 12) == 0)
    {
      showBlockedPCB();
    }
    else if (strncmp("show all", cmdBuffer, 8) == 0)
    {
      showAllPCB();
    }
    else if (strncmp("show", cmdBuffer, 4) == 0)
    {
      showPCB(cmdBuffer);
    }
    else if (strncmp("suspend", cmdBuffer, 7) == 0)
    {
      char *suspend = strtok(cmdBuffer, " ");
      suspend = strtok(NULL, " ");
      suspendPCB(suspend);
    }
    else if (strncmp("resume", cmdBuffer, 6) == 0)
    {
      char *resume = strtok(cmdBuffer, " ");
      resume = strtok(NULL, " ");
      resumePCB(resume);
    }
    else if (strncmp("set priority", cmdBuffer, 12) == 0)
    {
      //split cmd buffer to gather process name and priority
      char *proc_name, *number;
      int num_int;
      proc_name = strtok(cmdBuffer, " ");
      proc_name = strtok(NULL, " ");
      proc_name = strtok(NULL, " ");
      number = strtok(NULL, " ");
      num_int = atoi(number);

      setPCBPriority(proc_name, num_int);
    }

    else if (strncmp("loadr3", cmdBuffer, 6) == 0)
    {
      loadproc();
    }

    else if (strncmp("alarm", cmdBuffer, 5) == 0)
    {
      if (findPCB("alarm") == NULL)
      {
        updateAlarm(cmdBuffer);
        loadAlarm();
      }
      else
      {
        updateAlarm(cmdBuffer);
      }
    }
    else if (strncmp("infinite", cmdBuffer, 8) == 0)
    {
      if (findPCB("infinite") == NULL)
        loadInfinite();
    }
    else if (strncmp("init heap", cmdBuffer, 9) == 0)
    {
      //temp command to initialize heap to 1000 bytes
      initHeap(1000);
    }

    //user just presses enter, doesn't enter anything
    else if (strncmp("\r", cmdBuffer, 1) == 0)
    {
    } //do nothing

    //command not recognized
    else
    {
      println_error("Command not recognized");
    }

    if (!shutdown_flag)
      sys_req(IDLE, COM1, NULL, NULL);
  }

  return 0;
}
