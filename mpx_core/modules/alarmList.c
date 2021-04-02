/**
  @file alarmList.case
  implmenets alarmlist structure
*/

#include "alarmList.h"
#include "mpx_supt.h"
#include "pcb_func.h"
#include "perm_pcb_comm.h"
#include "temp_func.h"
#include <core/serial.h>
#include <string.h>

alarmlist listOfAlarms = {0, NULL, NULL};

alarm* setupAlarm(char *mess, int hours, int minutes, int seconds)
{
  alarm *new = sys_alloc_mem(sizeof(alarm));
  strcpy(new->message, mess);
  new->hours = hours;
  new->minutes = minutes;
  new->seconds = seconds;

  return new;
}


void removeAlarm(alarm *removed)
{
  if (removed == listOfAlarms.head && removed == listOfAlarms.tail)
  {
    listOfAlarms.head = NULL;
    listOfAlarms.tail = NULL;
    listOfAlarms.size--;
  }
  else if (removed == listOfAlarms.head)
  {
    listOfAlarms.head = listOfAlarms.head->next;
    listOfAlarms.size--;
  }
  else if (removed == listOfAlarms.tail)
  {
    removed->prev->next = NULL;
    listOfAlarms.tail = removed->prev;
    removed->prev = NULL;
    listOfAlarms.size--;
  }
  else
  {
    removed->prev->next = removed->next;
    removed->next->prev = removed->prev;
    removed->next = NULL;
    removed->prev = NULL;
    listOfAlarms.size--;
  }
  sys_free_mem(removed);

}

void addAlarm(alarm *alarmptr)
{
  if (listOfAlarms.head == NULL)
  {
    listOfAlarms.head = alarmptr;
    listOfAlarms.tail = alarmptr;
    listOfAlarms.size++;
    alarmptr->next = NULL;
    alarmptr->prev = NULL;
  }
  else
  {
    if (listOfAlarms.size == 1)
    {
      listOfAlarms.head->next = alarmptr;
      alarmptr->prev = listOfAlarms.head;
      alarmptr->next = NULL;
      listOfAlarms.tail = alarmptr;
      listOfAlarms.size++;
    }
    else
    {
      alarmptr->prev = listOfAlarms.tail;
      listOfAlarms.tail->next = alarmptr;
      alarmptr-> next = NULL;
      listOfAlarms.tail = alarmptr;
      listOfAlarms.size++;
    }
  }
}
