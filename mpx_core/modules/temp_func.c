/**
  @file temp_func.c
  Implementation of temprorary pcb functions/commands
*/

#include "temp_func.h"
#include "pcb_func.h"
#include <string.h>
#include <core/serial.h>
#include "queue.h"

void createPCB(char *params)
{
  //split the string
  char *temp1, *temp2, *name, *class, *priority;
  temp1 = strtok(params, " ");
  temp2 = strtok(NULL, " ");
  strncmp(temp1, temp2, 0);
  class = strtok(NULL, " ");
  name = strtok(NULL, " ");
  priority = strtok(NULL, " ");

  //length of name check
  if (strlen(name) > 19)
  {
    println_error("Name too long! 19 character max");
    return;
  }

  //convert priority to integer
  int priority_int = atoi(priority);

  //priority range must be valid
  if (priority_int > 9 || priority_int < 0)
  {
    println_error("Invalid priority value! Range: 0-9");
    return;
  }


  //check for unique name, not already taken
  if (findPCB(name) != NULL)
  {

    println_error("name must be unique!");
    return;
  }

  //checks for valid class
  if (strncmp(class, "application",11) != 0 && strncmp(class, "system", 6) != 0)
  {
    println_error("Invalid class! application or system");
    return;
  }

  //convert class to integer
  int class_int = atoi(class);

  if (strncmp(class, "application",11) == 0) class_int = 1;
  else class_int = 0;

  //setup new PCB and insert into the right queue
  pcb *new = setupPCB(name, class_int, priority_int);
  insertPCB(new);

}


void deletePCB(char *name)
{
  pcb *delete = findPCB(name);

  //makes sure name is valid
  if (delete == NULL)
  {
    println_error("PCB doesn't exist!");
    return;
  }

  if (strncmp(delete->name, "infinite", 8) == 0)
  {
    if (delete->suspended == NOT_SUSP)
    {
      println_error("Infinite must be suspended to delete!");
      return;
    }
  }

  removePCB(delete);
  freePCB(delete);

}


void blockPCB(char *name)
{
  char *temp1, *process;
  temp1 = strtok(name, " ");
  strcmp(temp1, "");
  process = strtok(NULL, " ");

  pcb *blocked = findPCB(process);

  //name is not valid
  if (blocked == NULL)
  {
    println_error("PCB doesn't exist!");
    return;
  }

  if (blocked->state == BLOCKED)
  {
    println_error("PCB is already blocked!");
    return;
  }

  removePCB(blocked);
  blocked->state = BLOCKED;
  insertPCB(blocked);

}

void unblockPCB(char *name)
{
  char *temp, *process;
  temp = strtok(name, " ");
  strncmp(temp, "", 0);
  process = strtok(NULL, " ");

  pcb *unblocked = findPCB(process);

  //name is not valid
  if (unblocked == NULL)
  {
    println_error("PCB doesn't exist!");
    return;
  }

  if (unblocked->state == READY)
  {
    println_error("PCB is already ready!");
    return;
  }

  removePCB(unblocked);
  unblocked->state = READY;
  insertPCB(unblocked);

}
