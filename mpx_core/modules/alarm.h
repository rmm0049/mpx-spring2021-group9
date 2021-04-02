/**
  @file alarm.h
  Header file for alarm PCB
*/

#ifndef _ALARM_H
#define _ALARM_H

/**
  Loads the alarm process into the system
  @param none
*/

void loadAlarm();

/**
  updates the list of alarms when a user enters new alarm
  @param char *command
*/

void updateAlarm(char *command);

/**
  Checks the list of alarms and sees if an alarm time has passed
  @param none
*/

void checkAlarm();


#endif
