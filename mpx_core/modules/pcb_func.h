/**
  @file pcb_func.h
  Defines all of the pcb operation functions as
  internal procedures
*/

#ifndef _PCB_FUNC_H
#define _PCB_FUNC_H

#include "pcb.h"
#include "queue.h"

/**
  Allocates new memory for new PCB
  @return PCB pointer
*/

pcb* allocatePCB();

/**
  Frees all memory associated with a given PCB
  @param PCB pointer
  @return success or error code
*/

int freePCB(pcb *pcb);

/**
  Creates an empty PCB, intializes PCB and sets the
  PCB state to ready, not suspended
  @param name, class, priority
  @return PCB pointer
*/

pcb* setupPCB(char *name, int class, int priority);

/**
  Searches all queues for a process with a given name
  @param Process name
  @return PCB pointer
*/

pcb* findPCB(char *name);

/**
  Inserts a PCB into the appropriate queue
  @param PCB pointer
*/

void insertPCB(pcb *pcb);

/**
  Removes a PCB from the queue in which it is currently stored
  @param PCB pointer
  @return success or error code
*/

int removePCB(pcb *pcb);




#endif
