/**
  @file pcb_func.c
  Implementation of pcb functions
*/

#include "pcb_func.h"
#include "queue.c"
#include "mpx_supt.h"
#include <string.h>

pcb *removed; //global pcb pointer for some odd reason ???
pcb *temp; //no idea yo

pcb* allocatePCB()
{
  return (sys_alloc_mem(sizeof(pcb)));
}

int freePCB(pcb *pcb)
{
  return (sys_free_mem(pcb));
}

pcb* setupPCB(char *name, int class, int priority)
{
  pcb *pcb = allocatePCB();
  pcb->name = name;
  pcb->class = class;
  pcb->priority = priority;
  pcb->state = READY;
  pcb->suspended = NOT_SUSP;

  // char test[1024];
  // memset(test, '\0', 1024);
  // strcpy(pcb->stack, test);
  // pcb->topStack = (pcb->stack);
  // pcb->baseStack = (pcb->stack+STACK_SIZE);

  return pcb;
}

pcb* findPCB(char *name)
{
  //read not suspended
  pcb *node = readyQueue.head;
  while (node != NULL)
  {
    if (strcmp(node->name, name) == 0)
      return node;
    node = node->next;
  }

  //ready suspended queue
  node = readySuspendedQueue.head;
  while (node != NULL)
  {
    if (strcmp(node->name, name) == 0)
      return node;
    node = node->next;
  }

  //blocked  queue
  node = blockedQueue.head;
  while (node != NULL)
  {
    if (strcmp(node->name, name) == 0)
      return node;
    node = node->next;
  }

  //blocked suspended queue
  node = blockedSuspendedQueue.head;
  while (node != NULL)
  {
    if (strcmp(node->name, name) == 0)
      return node;
    node = node->next;
  }

  return NULL;
}

void insertPCB(pcb *pcb)
{
  //ready not suspended queue (priority queue)
  if (pcb->state == READY && pcb->suspended == NOT_SUSP)
  {
    if (readyQueue.size == 0)
    {
      readyQueue.head = pcb;
      readyQueue.tail = pcb;
      readyQueue.size++;
      pcb->next = NULL;
      pcb->previous = NULL;
    }
    else
    {
      //new pcb priority is already greater than head of queue
      if (pcb->priority > readyQueue.head->priority)
      {
        pcb->next = readyQueue.head;
        readyQueue.head = pcb;
      }
      else
      {
        temp = readyQueue.head;
        while (temp->next != NULL && temp->next->priority <= temp->priority)
        {
          temp = temp->next;
        }

        if (temp == readyQueue.tail)
        {
          pcb->previous = readyQueue.tail;
          readyQueue.tail->next = pcb;
          pcb-> next = NULL;
          readyQueue.tail = pcb;
          readyQueue.size++;
        }
        else
        {
          pcb->next = temp->next;
          pcb->previous = temp;
          temp->next->previous = pcb;
          temp->next = pcb;
          readyQueue.size++;
        }
      }
    }
  }

  //ready suspended queue
  else if (pcb->state == READY && pcb->suspended == SUSPSEND)
  {
    if (readySuspendedQueue.size == 0)
    {
      readySuspendedQueue.head = pcb;
      readySuspendedQueue.tail = pcb;
      readySuspendedQueue.size++;
      pcb->next = NULL;
      pcb->previous = NULL;
    }
    else
    {
      if (pcb->priority > readySuspendedQueue.head->priority)
      {
        pcb->next = readySuspendedQueue.head;
        readySuspendedQueue.head = pcb;
      }
      else
      {
        temp = readySuspendedQueue.head;
        while (temp->next != NULL && temp->next->priority <= temp->priority)
        {
          temp = temp->next;
        }

        if (temp == readySuspendedQueue.tail)
        {
          pcb->previous = readySuspendedQueue.tail;
          readySuspendedQueue.tail->next = pcb;
          pcb-> next = NULL;
          readySuspendedQueue.tail = pcb;
          readySuspendedQueue.size++;
        }
        else
        {
          pcb->next = temp->next;
          pcb->previous = temp;
          temp->next->previous = pcb;
          temp->next = pcb;
          readySuspendedQueue.size++;
        }
      }
    }
  }

  //blocked not suspended queue
  else if (pcb->state == BLOCKED && pcb->suspended == NOT_SUSP)
  {
    if (blockedQueue.size == 0)
    {
      blockedQueue.head = pcb;
      blockedQueue.tail = pcb;
      blockedQueue.size++;
      pcb->next = NULL;
      pcb->previous = NULL;
    }
    else
    {
      pcb->previous = blockedQueue.tail;
      blockedQueue.tail->next = pcb;
      pcb-> next = NULL;
      blockedQueue.tail = pcb;
      blockedQueue.size++;
    }
  }

  //blocked suspended queue
  else if (pcb->state == BLOCKED && pcb->suspended == SUSPSEND)
  {
    if (blockedSuspendedQueue.size == 0)
    {
      blockedSuspendedQueue.head = pcb;
      blockedSuspendedQueue.tail = pcb;
      blockedSuspendedQueue.size++;
      pcb->next = NULL;
      pcb->previous = NULL;
    }
    else
    {
      pcb->previous = blockedSuspendedQueue.tail;
      blockedSuspendedQueue.tail->next = pcb;
      pcb-> next = NULL;
      blockedSuspendedQueue.tail = pcb;
      blockedSuspendedQueue.size++;
    }
  }

}

int removePCB(pcb *pcb)
{
  removed = findPCB(pcb->name);

  if (removed == NULL) return 1; //error not found

  //ready not suspended queue
  if (removed->state == READY && removed->suspended == NOT_SUSP)
  {
    if (removed == readyQueue.head)
    {
      readyQueue.head = readyQueue.head->next;
      readyQueue.size--;
    }
    else if (removed == readyQueue.tail)
    {
      readyQueue.tail->previous->next = NULL;
      readyQueue.tail = readyQueue.tail->previous;
      readyQueue.size--;
    }
    else
    {
      removed->previous->next = removed->next;
      removed->next = NULL;
    }
  }

  //ready suspended queue
  else if (removed->state == READY && removed->suspended == SUSPSEND)
  {
    if (removed == readySuspendedQueue.head)
    {
      readySuspendedQueue.head = readySuspendedQueue.head->next;
      readySuspendedQueue.size--;
    }
    else if (removed == readySuspendedQueue.tail)
    {
      readySuspendedQueue.tail->previous->next = NULL;
      readySuspendedQueue.tail = readySuspendedQueue.tail->previous;
      readySuspendedQueue.size--;
    }
    else
    {
      removed->previous->next = removed->next;
      removed->next = NULL;
    }
  }

  //blocked not suspended queue
  else if (removed->state == BLOCKED && removed->suspended == NOT_SUSP)
  {
    if (removed == blockedQueue.head)
    {
      blockedQueue.head = blockedQueue.head->next;
      blockedQueue.size--;
    }
    else if (removed == blockedQueue.tail)
    {
      blockedQueue.tail->previous->next = NULL;
      blockedQueue.tail = blockedQueue.tail->previous;
      blockedQueue.size--;
    }
    else
    {
      removed->previous->next = removed->next;
      removed->next = NULL;
    }
  }

  //blocked suspended queue
  else if (removed->state == BLOCKED && removed->suspended == SUSPSEND)
  {
    if (removed == blockedSuspendedQueue.head)
    {
      blockedSuspendedQueue.head = blockedSuspendedQueue.head->next;
      blockedSuspendedQueue.size--;
    }
    else if (removed == blockedSuspendedQueue.tail)
    {
      blockedSuspendedQueue.tail->previous->next = NULL;
      blockedSuspendedQueue.tail = blockedSuspendedQueue.tail->previous;
      blockedSuspendedQueue.size--;
    }
    else
    {
      removed->previous->next = removed->next;
      removed->next = NULL;
    }
  }

  return 0;

}
