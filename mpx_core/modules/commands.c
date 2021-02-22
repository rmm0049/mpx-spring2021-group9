/**
 @file commands.c
 Contains function commands() to display the available user commands
*/

#include "commands.h"
#include <core/serial.h>
#include "mpx_supt.h"
#include <core/io.h>
#include <string.h>


/**
  Outputs the current available user commands
*/

void commands()
{

  simple_print("\n");
  println_warning("AVAILABLE COMMANDS"); //overarching commands section

  println_confirmation(" Time and Date"); //subsection of time and date
  println_message("  gettime");
  println_message("  getdate");
  println_message("  settime");
  println_message("  setdate");

  println_confirmation(" Manipulate PCB"); //subsection of pcb manipulation
  println_message("  create PCB");
  println_message("  suspend");
  println_message("  resume");
  println_message("  block");
  println_message("  unblock");

  println_confirmation(" Show PCB"); //subsection of Show PCB
  println_message("  show all");
  println_message("  show ready");
  println_message("  show blocked");
  println_message("  show");

  println_confirmation(" Current Version"); //subsection of version
  println_message("  version");

  println_confirmation(" Command Usage Help"); //subsection of help
  println_message("  help");

  println_confirmation(" Shutdown Program"); //subsection of shutdown
  println_message("  shutdown");
  simple_print("\n");
}
