/**
  @file getdate.c
  Contains function getdate() to display the current date
*/

#include "getdate.h"
#include "gettime.h"
#include <core/serial.h>
#include "mpx_supt.h"
#include <core/io.h>
#include <string.h>


/**
  Displays the current date on the machine
*/

void getdate()
{
  //0x09 bottom two numbers for year
  //0x32 for first two numbers for year

  int count = 10;

  //day of week 0x06
  outb(0x70, 0x06);
  int week = (int) inb(0x71);
  int week_dec = BCDToDecimal(week);
  char weeks[2];
  itoa(week_dec, weeks, 10);

  char *dayOfWeek = "111 "; //placeholder

  //conditionals to print the correct day of week
  if (strncmp(weeks, "1", 1) == 0)
  {
      dayOfWeek[0] = 'S';
      dayOfWeek[1] = 'u';
      dayOfWeek[2] = 'n';
  }
  else if (strncmp(weeks, "2", 1) == 0)
  {
      dayOfWeek[0] = 'M';
      dayOfWeek[1] = 'o';
      dayOfWeek[2] = 'n';
  }
  else if (strncmp(weeks, "3", 1) == 0)
  {
      dayOfWeek[0] = 'T';
      dayOfWeek[1] = 'u';
      dayOfWeek[2] = 'e';
  }
  else if (strncmp(weeks, "4", 1) == 0)
  {
      dayOfWeek[0] = 'W';
      dayOfWeek[1] = 'e';
      dayOfWeek[2] = 'd';
  }
  else if (strncmp(weeks, "5", 1) == 0)
  {
      dayOfWeek[0] = 'T';
      dayOfWeek[1] = 'h';
      dayOfWeek[2] = 'u';
  }
  else if (strncmp(weeks, "6", 1) == 0)
  {
      dayOfWeek[0] = 'F';
      dayOfWeek[1] = 'r';
      dayOfWeek[2] = 'i';
  }
  else if (strncmp(weeks, "7", 1) == 0)
  {
      dayOfWeek[0] = 'S';
      dayOfWeek[1] = 'a';
      dayOfWeek[2] = 't';
  }


  sys_req(WRITE, COM1, dayOfWeek, &count);

  //day of month 0x07
  outb(0x70, 0x07);
  int month_day = (int) inb(0x71);
  int month_day_dec = BCDToDecimal(month_day);
  char month_days[2];
  itoa(month_day_dec, month_days, 10);
  sys_req(WRITE, COM1, month_days, &count);
  sys_req(WRITE, COM1, " ", &count);

  //month of year 0x08
  outb(0x70, 0x08);
  int month = (int) inb(0x71);
  int month_dec = BCDToDecimal(month);
  char months[2];
  itoa(month_dec, months, 10);

  char *month_word = "111 "; //placeholder

  //conditionals to disply correct month word
  if (strncmp(months, "1", 1) == 0)
  {
    month_word[0] = 'J';
    month_word[1] = 'a';
    month_word[2] = 'n';
  }
  else if (strncmp(months, "2", 1) == 0)
  {
    month_word[0] = 'F';
    month_word[1] = 'e';
    month_word[2] = 'b';
  }
  else if (strncmp(months, "3", 1) == 0)
  {
    month_word[0] = 'M';
    month_word[1] = 'a';
    month_word[2] = 'r';
  }
  else if (strncmp(months, "4", 1) == 0)
  {
    month_word[0] = 'A';
    month_word[1] = 'p';
    month_word[2] = 'r';
  }
  else if (strncmp(months, "5", 1) == 0)
  {
    month_word[0] = 'M';
    month_word[1] = 'a';
    month_word[2] = 'y';
  }
  else if (strncmp(months, "6", 1) == 0)
  {
    month_word[0] = 'J';
    month_word[1] = 'u';
    month_word[2] = 'n';
  }
  else if (strncmp(months, "7", 1) == 0)
  {
    month_word[0] = 'J';
    month_word[1] = 'u';
    month_word[2] = 'l';
  }
  else if (strncmp(months, "8", 1) == 0)
  {
    month_word[0] = 'A';
    month_word[1] = 'u';
    month_word[2] = 'g';
  }
  else if (strncmp(months, "9", 1) == 0)
  {
    month_word[0] = 'S';
    month_word[1] = 'e';
    month_word[2] = 'p';
  }
  else if (strncmp(months, "10", 2) == 0)
  {
    month_word[0] = 'O';
    month_word[1] = 'c';
    month_word[2] = 't';
  }
  else if (strncmp(months, "11", 2) == 0)
  {
    month_word[0] = 'N';
    month_word[1] = 'o';
    month_word[2] = 'v';
  }
  else if (strncmp(months, "12", 2) == 0)
  {
    month_word[0] = 'D';
    month_word[1] = 'e';
    month_word[2] = 'c';
  }


  sys_req(WRITE, COM1, month_word, &count);

  //year (0x09 and 0x32)
  outb(0x70, 0x32);
  int year_milenium = (int) inb(0x71);
  int year_milenium_dec = BCDToDecimal(year_milenium);
  char year_milenium_char[2];
  itoa(year_milenium_dec, year_milenium_char, 10);
  sys_req(WRITE, COM1, year_milenium_char, &count);

  outb(0x70, 0x09);
  int year_decade = (int) inb(0x71);
  int year_decade_dec = BCDToDecimal(year_decade);
  char year_decade_char[2];
  itoa(year_decade_dec, year_decade_char, 10);

  //if decade is 00
  if (year_decade_dec == 0)
  {
    sys_req(WRITE, COM1, "00", &count);
    sys_req(WRITE, COM1, "\n", &count);
    return;
  }

  sys_req(WRITE, COM1, year_decade_char, &count);
  sys_req(WRITE, COM1, "\n", &count);


}
