/**
  @file setdate.c
  contains setdate(char *date) function to set a new date on the system
*/

#include "gettime.h"
#include "setdate.h"
#include <core/serial.h>
#include "mpx_supt.h"
#include <core/io.h>
#include <string.h>


/**
  sets the date to the given input
  @param char *date
*/

void setdate(char *date)
{
  char *date_space, *dayOfWeek, *day, *month, *year;

  //split the string into each part of the date
  date_space = strtok(date, " ");
  strncmp(date_space, NULL, 0);
  dayOfWeek = strtok(NULL, " ");
  day = strtok(NULL, " ");
  month = strtok(NULL, " ");
  year = strtok(NULL, " ");
  int week = 0;

  //day of the week
  if (strncmp(dayOfWeek, "Mon", 3) == 0)
  {
    week = 2;
  }
  else if (strncmp(dayOfWeek, "Tue", 3) == 0)
  {
    week = 3;
  }
  else if (strncmp(dayOfWeek, "Wed", 3) == 0)
  {
    week = 4;
  }
  else if (strncmp(dayOfWeek, "Thu", 3) == 0)
  {
    week = 5;
  }
  else if (strncmp(dayOfWeek, "Fri", 3) == 0)
  {
    week = 6;
  }
  else if (strncmp(dayOfWeek, "Sat", 3) == 0)
  {
    week = 7;
  }
  else if (strncmp(dayOfWeek, "Sun", 3) == 0)
  {
    week = 1;
  }
  else
  {
    serial_println("Invalid format");
    return;
  }

  cli();
  outb(0x70, 0x06);
  outb(0x71, DecimalToBCD(week));
  sti();

  //day
  int day_value = atoi(day);
  if (day_value > 31 || day_value < 0)
  {
    serial_println("Invalid format");
    return;
  }

  cli();
  outb(0x70, 0x07);
  outb(0x71, DecimalToBCD(day_value));
  sti();

  //month
  int month_num = 0;
  if (strncmp(month, "Jan", 3) == 0)
  {
    month_num = 1;
  }
  else if (strncmp(month, "Feb", 3) == 0)
  {
    month_num = 2;
  }
  else if (strncmp(month, "Mar", 3) == 0)
  {
    month_num = 3;
  }
  else if (strncmp(month, "Apr", 3) == 0)
  {
    month_num = 4;
  }
  else if (strncmp(month, "May", 3) == 0)
  {
    month_num = 5;
  }
  else if (strncmp(month, "Jun", 3) == 0)
  {
    month_num = 6;
  }
  else if (strncmp(month, "Jul", 3) == 0)
  {
    month_num = 7;
  }
  else if (strncmp(month, "Aug", 3) == 0)
  {
    month_num = 8;
  }
  else if (strncmp(month, "Sep", 3) == 0)
  {
    month_num = 9;
  }
  else if (strncmp(month, "Oct", 3) == 0)
  {
    month_num = 10;
  }
  else if (strncmp(month, "Nov", 3) == 0)
  {
    month_num = 11;
  }
  else if (strncmp(month, "Dec", 3) == 0)
  {
    month_num = 12;
  }
  else
  {
    serial_println("Invalid format");
    return;
  }

  cli();
  outb(0x70, 0x08);
  outb(0x71, DecimalToBCD(month_num));
  sti();

  //year need to break it up
  if (strlen(year) != 4)
  {
    serial_println("Invalid format");
    return;
  }


  int year_int = atoi(year);

  //calculate the milenium and decade based on year
  int milenium = year_int / 100;
  int decade = year_int % 100;


  //milenium first two digits
  cli();
  outb(0x70, 0x32);
  outb(0x71, DecimalToBCD(milenium));
  sti();

  //decade last two digits
  cli();
  outb(0x70, 0x09);
  outb(0x71, DecimalToBCD(decade));
  sti();

}
