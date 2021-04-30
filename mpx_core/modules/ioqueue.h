/**
  @file ioqueue.h
  Defines the struct of a queue to use for containing IO requests
*/

#ifndef _QUEUE_H
#define _QUEUE_H

#include "iocb.h"

typedef struct ioqueue
{
    int size;   //keeps track of amount in queue
    iocb *head; //pointer to the head IOCB
    iocb *tail; //pointer to the tail IOCB

} ioqueue;

extern ioqueue ioQueue;

#endif