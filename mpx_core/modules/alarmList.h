/**
  @file alarmList.h
*/

#ifndef _ALARM_LIST_H
#define _ALARM_LIST_H

/**
  defines alarm struct
*/

typedef struct alarm {
  char message[50];
  int hours;
  int minutes;
  int seconds;
  struct alarm *next;
  struct alarm *prev;

} alarm;

/**
  defines double linked list of alarms
*/

typedef struct alarmlist {
  int size;
  struct alarm *head;
  struct alarm *tail;
} alarmlist;

/**
  removes an alarm from the list
  @param alarm *removed
*/

void removeAlarm(alarm *removed);

/**
  adds an alarm to the list
  @param alarm *alarmptr
*/

void addAlarm(alarm *alarmptr);

/**
  sets up a new alarm struct
  @param char *message, int hour, int minute, int second
  @return alarm*
*/

alarm* setupAlarm(char *mess, int hour, int minute, int second);

///exports the listOfAlarms double linked list
extern alarmlist listOfAlarms;



#endif
