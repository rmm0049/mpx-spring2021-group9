/*
    -----comhand.c-------

  Description: handles the input commands from the command line
*/

#include "comhand.h"
#include "mpx_supt.h"
#include <core/serial.h>
#include <string.h>



int comhandler()
{
  char cmdBuffer[BUFFER];
  int bufferSize;
  int quit = 0;

  while (!quit)
  {
    memset(cmdBuffer, '\0', 100);
    bufferSize = 99;
    sys_req(READ, COM1, cmdBuffer, &bufferSize);

    //just testing
    serial_println(cmdBuffer);

    /*
      Commands for R1
      version, help, shutdown, getate, setdate, gettime, settime
    */

    //version command

    //shutdown command

    //help command

    //date Commands

    //time commands


  }

  return 0;
}
