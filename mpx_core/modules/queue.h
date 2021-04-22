/**
  @file queue.h
  Defines the struct of a queue to use for containing PCBs
*/

#ifndef _QUEUE_H
#define _QUEUE_H

typedef struct queue
{
  int size;   //keeps track of amount in queue
  void *head; //pointer to the head PCB
  void *tail; //pointer to the tail PCB

} queue;

extern queue readyQueue;
extern queue readySuspendedQueue;
extern queue blockedQueue;
extern queue blockedSuspendedQueue;
extern queue ioQueue;

#endif
