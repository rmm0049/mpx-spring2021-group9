/**
  @file perm_pcb_comm.h
  Function definitions for permanent pcb user commands
*/

#ifndef _PERM_PCB_COMM_H
#define _PERM_PCB_COMM_H

/**
  Places the PCB into the suspended state and reinserts
  into the appropriate queue
  @param char *name
*/

void suspendPCB(char *name);

/**
  Places PCB into the not suspended state and reinserts it into
  the appropriate queue
  @param char *name
*/

void resumePCB(char *name);

/**
  Sets a PCB's priority and reinserts the process into the correct
  place in the correct queue
  @param char *name, int priority
*/

void setPCBPriority(char *name, int priority);

/**
  Displays the attributes for a PCB
  @param char *name
*/

void showPCB(char *name);

/**
  Displays all of the PCBs in the ready queues
*/

void showReadyPCB();

/**
  Displays all of the PCBs in the blocked queues
*/

void showBlockedPCB();

/**
  Shows all PCBs in all of the queues
*/

void showAllPCB();



#endif
