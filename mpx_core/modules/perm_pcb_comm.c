/**
  @file perm_pcb_comm.c
  Function implementations of permanent PCB functions for
  user commands
*/

#include "perm_pcb_comm.h"
#include <string.h>
#include "pcb_func.h"
#include <core/serial.h>
#include "queue.h"

int flag = 0;


void suspendPCB(char *name)
{
  // char *process = strtok(name, " ");
  // process = strtok(NULL, " ");
  pcb *pcb = findPCB(name);

  if (pcb == NULL)
  {
    println_error("PCB doesn't exist!");
    return;
  }

  //checks to make sure pcb is not already suspended
  if (pcb->suspended == SUSPSEND)
  {
    println_error("PCB is already suspended!");
    return;
  }

  if (!pcb->class)
  {
    println_error("Can't manipulate system process!");
    return;
  }

  removePCB(pcb);
  pcb->suspended = SUSPSEND;
  insertPCB(pcb);

}

void resumePCB(char *name)
{
  // char *process = strtok(name, " ");
  // process = strtok(NULL, " ");
  pcb *pcb = findPCB(name);

  if (pcb == NULL)
  {
    println_error("PCB doesn't exist!");
    return;
  }

  if (!pcb->class)
  {
    println_error("Can't manipulate system process!");
    return;
  }

  //checks to make sure pcb is not already not suspended
  if (pcb->suspended == NOT_SUSP)
  {
    println_error("PCB is already not suspended!");
    return;
  }


  removePCB(pcb);
  pcb->suspended = NOT_SUSP;
  insertPCB(pcb);
}

void setPCBPriority(char *name, int priority)
{
  pcb *pcb = findPCB(name);

  if (pcb == NULL)
  {
    println_error("PCB doesn't exist!");
    return;
  }

  if (priority > 9 || priority < 0)
  {
    println_error("priority out of bounds! Range: 0-9");
    return;
  }

  removePCB(pcb);
  pcb->priority = priority;
  insertPCB(pcb);

}



void showPCB(char *name)
{
  char *temp, *process;
  if (!flag)
  {
    temp = strtok(name, " ");
    process = strtok(NULL, " ");
    strcmp(temp, "");
  }
  else
  {
    process = name;
    flag = 0;
  }

  pcb *pcb = findPCB(process);

  //checks that name is valid
  if (pcb == NULL)
  {
    println_error("PCB doesn't exist!");
    return;
  }

  int class_int = pcb->class;
  char *class;

  int state_int = pcb->state;
  char *state;

  int suspended_int = pcb->suspended;
  char *susp_status;

  char mess[2];
  char *priority = itoa(pcb->priority, mess, 10);

  //class of PCB
  switch (class_int)
  {
    case 0:
      class = "System";
      break;
    case 1:
      class = "Application";
      break;
    default:
      break;
  }

  //state of PCB
  switch (state_int)
  {
    case 0:
      state = "Ready";
      break;
    case 1:
      state = "Running";
      break;
    case 2:
      state = "Blocked";
      break;
    default:
      break;
  }

  //suspended status of PCB
  switch (suspended_int)
  {
    case 0:
      susp_status = "Not Suspended";
      break;
    case 1:
      susp_status = "Suspended";
      break;
    default:
      break;
  }

  print_confirmation("Process name: ");
  println_message(pcb->name);

  print_confirmation("Class: ");
  println_message(class);

  print_confirmation("Priority: ");
  println_message(priority);

  print_confirmation("State: ");
  println_message(state);

  print_confirmation("Suspended Status: ");
  println_message(susp_status);

  println_message("-------------------------");

}


void showReadyPCB()
{
  pcb *temp = readyQueue.head;

  println_warning("READY NOT SUSPENDED");
  println_message("******************************************");

  if (temp == NULL)
  {
    println_error("Empty");
  }


  while (temp != NULL)
  {
    flag = 1;
    showPCB(temp->name);
    temp = temp->next;
  }
  println_message("******************************************");

  println_warning("READY SUSPENDED");
  println_message("******************************************");
  temp = readySuspendedQueue.head;

  if (temp == NULL)
  {
    println_error("Empty");
  }


  while (temp != NULL)
  {
    flag = 1;
    showPCB(temp->name);
    temp = temp->next;
  }
  println_message("******************************************");
}


void showBlockedPCB()
{
  pcb *temp = blockedQueue.head;
  println_warning("BLOCKED NOT SUSPENDED");
  println_message("******************************************");

  if (temp == NULL)
  {
    println_error("Empty");
  }

  while (temp != NULL)
  {
    flag = 1;
    showPCB(temp->name);
    temp = temp->next;
  }


  println_message("******************************************");
  println_warning("BLOCKED SUSPENDED");
  println_message("******************************************");

  temp = blockedSuspendedQueue.head;
  if (temp == NULL)
  {
    println_error("Empty");
  }


  while (temp != NULL)
  {
    flag = 1;
    showPCB(temp->name);
    temp = temp->next;
  }
  println_message("******************************************");
}

void showAllPCB()
{
  simple_print("\n");
  showReadyPCB();
  showBlockedPCB();
  simple_print("\n");
}
