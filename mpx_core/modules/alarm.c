/**
  @file alarm.c
  Implementation of alarm PCB
*/

#include "alarm.h"
#include "pcb.h"
#include <core/context.h>
#include <core/serial.h>
#include "pcb.h"
#include "temp_func.h"
#include <core/io.h>
#include "pcb_func.h"
#include "gettime.h"
#include "perm_pcb_comm.h"
#include "comhand.h"
#include "mpx_supt.h"
#include "alarmList.h"
#include <string.h>
#include <system.h>

pcb *globalAlarm = NULL;
int exit = 0;

void loadAlarm()
{
  pcb *alarmpcb = setupPCB("alarm", 1, 0);
  context *alarmcp = (context *) (alarmpcb->topStack);
  memset(alarmcp, 0, sizeof(context));
  alarmcp->fs = 0x10;
  alarmcp->gs = 0x10;
  alarmcp->ds = 0x10;
  alarmcp->es = 0x10;
  alarmcp->cs = 0x08;
  alarmcp->ebp = (u32int) alarmpcb->stack;
  alarmcp->esp = (u32int) alarmpcb->topStack;
  alarmcp->eip = (u32int) checkAlarm;
  alarmcp->eflags = 0x202;

  insertPCB(alarmpcb);

}

void checkAlarm()
{
  while (!exit){

    //gets current hour
    outb(0x70, 0x04);
    int hour = (int) inb(0x71);
    int hour_dec = BCDToDecimal(hour);

    // //gets current minute
    outb(0x70, 0x02);
    int min = (int) inb(0x71);
    int min_dec = BCDToDecimal(min);

    // //gets current second
    outb(0x70, 0x00);
    int sec = (int) inb(0x71);
    int sec_dec = BCDToDecimal(sec);

    alarm *loop = listOfAlarms.head;

    while(loop != NULL)
    {
      if (loop->hours < hour_dec)
      {
        println_message(loop->message);
        removeAlarm(loop);
      }
      else if (loop->hours == hour_dec)
      {
        if (loop->minutes < min_dec)
        {
          println_message(loop->message);
          removeAlarm(loop);
        }
        else if (loop->minutes == min_dec)
        {
          if (loop->seconds <= sec_dec)
          {
            println_message(loop->message);
            removeAlarm(loop);
          }
        }
      }
      loop = loop->next;
    }

    sys_req(IDLE, COM1, NULL, NULL);
  }

}

void updateAlarm(char *command)
{
  char *message, *time_split;
  char *time[3];
  int i = 0;
  message = strtok(command, "\"");
  message = strtok(NULL, "\"");

  time_split = strtok(NULL, " :"); //breaks the time change into hours, minutes and seconds
  while (time_split != NULL)
  {
    time[i++] = time_split;
    time_split = strtok(NULL, ":");
  }

  int hours = atoi(time[0]);
  int minutes = atoi(time[1]);
  int seconds = atoi(time[2]);

  if (hours > 24 || hours < 0 || minutes > 60 || minutes < 0 || seconds > 60 || seconds < 0)
  {
    println_error("Invalid format!");
    return;
  }

  if (strlen(message) > 50)
  {
    println_error("Message too long!");
    return;
  }


  alarm *newAlarm = setupAlarm(message, hours, minutes, seconds);
  addAlarm(newAlarm);

}
