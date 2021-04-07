/**
  @file settime.c
  Sets a new time given by the user
*/

#include "gettime.h"
#include "settime.h"
#include <core/serial.h>
#include "mpx_supt.h"
#include <core/io.h>
#include <string.h>

/**
  Allows user to change the time on the system
  @param char *time
*/

void settime(char *time)
{
  char *time_space, *time_change, *time_split;
  int i = 0; // count = 10;
  char *t[3];
  time_space = strtok(time, " ");

  while (time_space != NULL) // breaks the command into two parts for the actual time change
  {
    time_change = time_space;
    time_space = strtok(NULL, " ");
  }

  if (strlen(time_change) != 8) //if not in the right format, just return
  {
    println_error("Invalid format");
    println_message("Usage: settime hh:mm:ss\n");
    return;
  }

  time_split = strtok(time_change, ":"); //breaks the time change into hours, minutes and seconds
  while (time_split != NULL)
  {
    t[i++] = time_split;
    time_split = strtok(NULL, ":");
  }

  int hours = atoi(t[0]);
  int minutes = atoi(t[1]);
  int seconds = atoi(t[2]);

  //checks bounds for setting time
  if (hours > 24 || hours < 0 || minutes > 60 || minutes < 0 || seconds > 60 || seconds < 0)
  {
    println_error("Invalid format, out of bounds");
    println_message("Usage: settime hh:mm:ss");
    return;
  }

  //converts the decimal input into BCD format
  hours = DecimalToBCD(atoi(t[0]));
  minutes = DecimalToBCD(atoi(t[1]));
  seconds = DecimalToBCD(atoi(t[2]));

  //hours
  cli();
  outb(0x70, 0x04);
  outb(0x71, hours);
  sti();

  //minutes
  cli();
  outb(0x70, 0x02);
  outb(0x71, minutes);
  sti();

  //seconds
  cli();
  outb(0x70, 0x00);
  outb(0x71, seconds);
  sti();
}
