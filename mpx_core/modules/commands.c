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
  // int count = 10;
  println_message("\x1b[32mAVAILABLE COMMANDS:");
  println_message("   Current Version:");
  println_message("      \x1b[36mversion");
  println_message("   \x1b[32mCommand Usage Help:");
  println_message("     \x1b[36mhelp");
  println_message("   \x1b[32mShutdown Program:");
  println_message("     \x1b[36mshutdown");
  println_message("   \x1b[32mClear Screen:");
  println_message("     \x1b[36mclear");

  println_message("   \x1b[32mTime and Date:");
  println_message("      \x1b[36mgettime");
  println_message("      getdate");
  println_message("      settime");
  println_message("      setdate");

  println_message("   \x1b[32mProcess Control Blocks:");
  println_message("      \x1b[36msuspend");
  println_message("      resume");
  println_message("      set priority");
  println_message("      show");
  println_message("      show all");
  println_message("      show ready");
  println_message("      show blocked");
  println_message("      delete PCB");

  println_message("   \x1b[32mMemory Control Blocks:");
  println_message("      \x1b[36mshow free");
  println_message("      \x1b[36mshow allocated");

  println_message("   \x1b[32mAlarm:");
  println_message("      \x1b[36malarm");

  println_message("   \x1b[32mProcess Commands:");
  println_message("      \x1b[36minfinite");
  println_message("      \x1b[36mloadr3");

  println_message("   \x1b[32mAliasing:");
  println_message("      \x1b[36malias");

  simple_print("\x1b[0m");

  // sys_req(WRITE, COM1, "\x1b[32mAVAILABLE COMMANDS:\n", &count); //change color to green
  // sys_req(WRITE, COM1, "   Current Version:\n", &count);         //subsection of version
  // sys_req(WRITE, COM1, "      \x1b[36mversion\n", &count);

  // sys_req(WRITE, COM1, "   \x1b[32mCommand Usage Help:\n", &count); //subsection of help
  // sys_req(WRITE, COM1, "      \x1b[36mhelp\n", &count);

  // sys_req(WRITE, COM1, "   \x1b[32mShutdown Program:\n", &count); //subsection of shutdown
  // sys_req(WRITE, COM1, "      \x1b[36mshutdown\n", &count);

  // sys_req(WRITE, COM1, "   \x1b[32mTime and Date:\n", &count); //subsection of time and date
  // sys_req(WRITE, COM1, "      \x1b[36mgettime\n", &count);
  // sys_req(WRITE, COM1, "      getdate\n", &count);
  // sys_req(WRITE, COM1, "      settime\n", &count);
  // sys_req(WRITE, COM1, "      setdate\n", &count);

  // sys_req(WRITE, COM1, "   \x1b[32mProcess Control Blocks:\n", &count); //subsection of permanent PCB
  // sys_req(WRITE, COM1, "      \x1b[36msuspend\n", &count);
  // sys_req(WRITE, COM1, "      resume\n", &count);
  // sys_req(WRITE, COM1, "      set priority\n", &count);
  // sys_req(WRITE, COM1, "      show\n", &count);
  // sys_req(WRITE, COM1, "      show all\n", &count);
  // sys_req(WRITE, COM1, "      show ready\n", &count);
  // sys_req(WRITE, COM1, "      show blocked\n", &count);
  // sys_req(WRITE, COM1, "      delete PCB\n", &count);

  // sys_req(WRITE, COM1, "   \x1b[32mMemory Control Blocks:\n", &count);
  // sys_req(WRITE, COM1, "      \x1b[36mshow free\n", &count);
  // sys_req(WRITE, COM1, "      \x1b[36mshow allocated\n", &count);

  // sys_req(WRITE, COM1, "   \x1b[32mAlarm:\n", &count);
  // sys_req(WRITE, COM1, "      \x1b[36malarm\n", &count);

  // sys_req(WRITE, COM1, "   \x1b[32mProcess Commands:\n", &count);
  // sys_req(WRITE, COM1, "      \x1b[36minfinite\n", &count);
  // sys_req(WRITE, COM1, "      \x1b[36mloadr3\n", &count);

  // sys_req(WRITE, COM1, "   \x1b[32mAliasing:\n", &count);
  // sys_req(WRITE, COM1, "      \x1b[36malias\n", &count);

  // sys_req(WRITE, COM1, "\x1b[0m", &count); //change color back to default
}
