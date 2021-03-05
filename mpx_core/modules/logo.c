/**
 @file logo.c
 Contains function logo() to display the Group9 logo
*/

#include "commands.h"
#include <core/serial.h>
#include "mpx_supt.h"
#include <core/io.h>
#include <string.h>
/*
         *****
         *****
       *********

*/

/**
  Outputs the Group9 logo to the screen
*/

void logo()
{
  int count = 10;

  sys_req(WRITE, COM1, "         \x1b[41m     \x1b[0m\n", &count); //change background color to red and back to default
  sys_req(WRITE, COM1, "        \x1b[41m       \x1b[0m\n", &count); //change background color to red and back to default
  sys_req(WRITE, COM1, "       \x1b[41m         \x1b[0m\n", &count); //change background color to red and back to default

  sys_req(WRITE, COM1, "\x1b[101m")
}
