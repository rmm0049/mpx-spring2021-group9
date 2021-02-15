/**
  @file queue.h
  Defines the struct of a queue to use for containing PCBs
*/

#ifndef _QUEUE_H
#define _QUEUE_H

#include "pcb.h"

typedef struct queue
{
  int size; //keeps track of amount in queue
  pcb *head; //pointer to the head PCB
  pcb *tail; //pointer to the tail PCB

} queue;


#endif
