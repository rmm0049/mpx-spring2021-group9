/*
-----gettime.c-----
*/

#include "gettime.h"
#include <core/serial.h>
#include "mpx_supt.h"
#include <core/io.h>
#include <string.h>


/*
  Gets the current time running on the system
*/

void gettime()
{
  int count = 10;
  
  //hours
  outb(0x70, 0x04);
  int hour = (int) inb(0x71);
  int hour_dec = BCDToDecimal(hour);
  char hours[2];
  itoa(hour_dec, hours, 10);
  sys_req(WRITE, COM1, hours, &count);
  sys_req(WRITE, COM1, ":", &count);

  //minutes
  outb(0x70, 0x02);
  int min = (int) inb(0x71);
  int min_dec = BCDToDecimal(min);
  char minutes[2];
  itoa(min_dec, minutes, 10);
  sys_req(WRITE, COM1, minutes, &count);
  sys_req(WRITE, COM1, ":", &count);

  //seconds
  outb(0x70, 0x00);
  int sec = (int) inb(0x71);
  int sec_dec = BCDToDecimal(sec);
  char seconds[2];
  itoa(sec_dec, seconds, 10);
  sys_req(WRITE, COM1, seconds, &count);
  sys_req(WRITE, COM1, "\n", &count);


}

int BCDToDecimal(int BCD)
{
  return (((BCD>>4)*10) + (BCD & 0xF));
}

int DecimalToBCD(int decimal)
{
  return (((decimal / 10) << 4) | (decimal % 10));
}
