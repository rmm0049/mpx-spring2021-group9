/**
  @file pcb_func.c
  Implementation of pcb functions
*/

#include "pcb_func.h"
#include "queue.h"
#include "mpx_supt.h"
#include <string.h>
#include <core/serial.h>
#include <core/context.h>

pcb *removed; //global pcb pointer for some odd reason ???
pcb *temp; //no idea yo
pcb *parent;

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
  strcpy(pcb->name, name);
  pcb->class = class;
  pcb->priority = priority;
  pcb->state = READY;
  pcb->suspended = NOT_SUSP;

  memset(pcb->stack, 0, 1024);

  pcb->baseStack = pcb->stack;
  pcb->topStack = pcb->baseStack + 1024 - sizeof(struct context);

  return pcb;
}

pcb* findPCB(char *name)
{
  //read not suspended
  pcb *node = readyQueue.head;

  while (node != NULL)
  {

    if (strcmp(node->name, name) == 0)
    {
      return node;
    }
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
  struct pcb *ready = (struct pcb *)readyQueue.head;
  struct pcb *readySuspended = (struct pcb *)readySuspendedQueue.head;
  struct pcb *blocked = (struct pcb *)blockedQueue.head;
  struct pcb *blockedSuspended = (struct pcb *)blockedSuspendedQueue.head;



  //ready not suspended queue (priority queue)
  if (pcb->state == READY && pcb->suspended == NOT_SUSP)
  {
    //first queue insertion, intializes head and tail
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
      if (pcb->priority > ready->priority)
      {
        pcb->next = readyQueue.head; //new PCB's next points to current head
        ready->previous = pcb; //sets currnet head's previous to new PCB
        readyQueue.head = pcb; //head becomes new PCB
        pcb->previous = NULL; //new PCB's previous becomes NULL as it's the new head

        readyQueue.size++;

      }
      else
      {

        temp = readyQueue.head;
        int prior = pcb->priority; //priority of new PCB being inserted

        //Loops through to find where to insert new PCB
        while (temp->next != NULL && temp->priority >= prior )
        {
          temp = temp->next;
        }


        //if new PCB priority is bigger than temp, goes to previous node
        if (temp->priority < prior)
          temp = temp->previous;


        //if we're inserting at the tail
        if (temp == readyQueue.tail)
        {
            //head and tail at the same thing
            if (temp == readyQueue.head)
            {
              ready->next = pcb;
              ready->next = pcb;
              pcb->previous = readyQueue.head;
              pcb->next = NULL;
              readyQueue.tail = pcb;
              readyQueue.size++;
            }
            else
            {
              //normal insertion at the end of queue
              pcb->previous = readyQueue.tail;
              ready->next = pcb;
              pcb->next = NULL;
              readyQueue.tail = pcb;
              readyQueue.size++;
            }

        }
        //insertion in the middle of queue
        else
        {
          pcb->next = temp->next;
          pcb->previous = temp;
          temp->next->previous = pcb; //makes node to right of temp connect back to pcb thus inserting in middle
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
      //new pcb priority is already greater than head of queue
      if (pcb->priority > readySuspended->priority)
      {
        pcb->next = readySuspendedQueue.head; //new PCB's next points to current head
        readySuspended->previous = pcb; //sets currnet head's previous to new PCB
        readySuspended = pcb; //head becomes new PCB
        pcb->previous = NULL; //new PCB's previous becomes NULL as it's the new head

        readySuspendedQueue.size++;

      }
      else
      {

        temp = readySuspendedQueue.head;
        int prior = pcb->priority; //priority of new PCB being inserted

        //Loops through to find where to insert new PCB
        while (temp->next != NULL && temp->priority >= prior )
        {
          temp = temp->next;
        }


        //if new PCB priority is bigger than temp, goes to previous node
        if (temp->priority < prior)
          temp = temp->previous;


        //if we're inserting at the tail
        if (temp == readySuspendedQueue.tail)
        {
            //head and tail at the same thing
            if (temp == readySuspendedQueue.head)
            {
              readySuspended->next = pcb;
              readySuspended->next = pcb;
              pcb->previous = readySuspendedQueue.head;
              pcb->next = NULL;
              readySuspendedQueue.tail = pcb;
              readySuspendedQueue.size++;
            }
            else
            {
              //normal insertion at the end of queue
              pcb->previous = readySuspendedQueue.tail;
              readySuspended->next = pcb;
              pcb->next = NULL;
              readySuspendedQueue.tail = pcb;
              readySuspendedQueue.size++;
            }

        }
        //insertion in the middle of queue
        else
        {
          pcb->next = temp->next;
          pcb->previous = temp;
          temp->next->previous = pcb; //makes node to right of temp connect back to pcb thus inserting in middle
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
      if (blockedQueue.size == 1)
      {
        blocked->next = pcb;
        pcb->previous = blockedQueue.head;
        pcb->next = NULL;
        blockedQueue.tail = pcb;
        blockedQueue.size++;
      }
      else
      {
        pcb->previous = blockedQueue.tail;
        blocked->next = pcb;
        pcb-> next = NULL;
        blockedQueue.tail = pcb;
        blockedQueue.size++;
      }
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
      if (blockedSuspendedQueue.size == 1)
      {
        blockedSuspended->next = pcb;
        pcb->previous = blockedSuspendedQueue.head;
        pcb->next = NULL;
        blockedSuspendedQueue.tail = pcb;
        blockedSuspendedQueue.size++;
      }
      else
      {
        pcb->previous = blockedSuspendedQueue.tail;
        blockedSuspended->next = pcb;
        pcb-> next = NULL;
        blockedSuspendedQueue.tail = pcb;
        blockedSuspendedQueue.size++;
      }
    }
  }

}

int removePCB(pcb *pcb)
{
  struct pcb *ready = (struct pcb *)readyQueue.head;
  struct pcb *readySuspended = (struct pcb *)readySuspendedQueue.head;
  struct pcb *blocked = (struct pcb *)blockedQueue.head;
  struct pcb *blockedSuspended = (struct pcb *)blockedSuspendedQueue.head;
  removed = findPCB(pcb->name);

  if (removed == NULL) return 1; //error not found

  //ready not suspended queue
  if (removed->state == READY && removed->suspended == NOT_SUSP)
  {
    if (removed == readyQueue.head && removed == readyQueue.tail)
    {
      readyQueue.head = NULL;
      readyQueue.tail = NULL;
      readyQueue.size--;
    }
    else if (removed == readyQueue.head)
    {
      readyQueue.head = ready->next;
      readyQueue.size--;
    }
    else if (removed == readyQueue.tail)
    {
      removed->previous->next = NULL;
      readyQueue.tail = removed->previous;
      removed->previous = NULL;
      readyQueue.size--;
    }
    else
    {
      removed->previous->next = removed->next;
      removed->next->previous = removed->previous;
      removed->next = NULL;
      removed->previous = NULL;
      readyQueue.size--;
    }

  }

  //ready suspended queue
  else if (removed->state == READY && removed->suspended == SUSPSEND)
  {
    if (removed == readySuspendedQueue.head && removed == readySuspendedQueue.tail)
    {
      readySuspendedQueue.head = NULL;
      readySuspendedQueue.tail = NULL;
      readySuspendedQueue.size--;
    }
    else if (removed == readySuspendedQueue.head)
    {
      readySuspendedQueue.head = readySuspended->next;
      readySuspendedQueue.size--;
    }
    else if (removed == readySuspendedQueue.tail)
    {
      removed->previous->next = NULL;
      readySuspendedQueue.tail = removed->previous;
      removed->previous = NULL;
      readySuspendedQueue.size--;
    }
    else
    {
      removed->previous->next = removed->next;
      removed->next->previous = removed->previous;
      removed->next = NULL;
      removed->previous = NULL;
      readySuspendedQueue.size--;
    }
  }

  //blocked not suspended queue
  else if (removed->state == BLOCKED && removed->suspended == NOT_SUSP)
  {
    if (removed == blockedQueue.head && removed == blockedQueue.tail)
    {
      blockedQueue.head = NULL;
      blockedQueue.tail = NULL;
      blockedQueue.size--;
    }
    else if (removed == blockedQueue.head)
    {
      blockedQueue.head = blocked->next;
      blockedQueue.size--;
    }
    else if (removed == blockedQueue.tail)
    {
      removed->previous->next = NULL;
      blockedQueue.tail = removed->previous;
      removed->previous = NULL;
      blockedQueue.size--;
    }
    else
    {
      removed->previous->next = removed->next;
      removed->next->previous = removed->previous;
      removed->next = NULL;
      removed->previous = NULL;
      blockedQueue.size--;
    }
  }

  //blocked suspended queue
  else if (removed->state == BLOCKED && removed->suspended == SUSPSEND)
  {
    if (removed == blockedSuspendedQueue.head && removed == blockedSuspendedQueue.tail)
    {
      blockedSuspendedQueue.head = NULL;
      blockedSuspendedQueue.tail = NULL;
      blockedSuspendedQueue.size--;
    }
    else if (removed == blockedSuspendedQueue.head)
    {
      blockedSuspendedQueue.head = blockedSuspended->next;
      blockedSuspendedQueue.size--;
    }
    else if (removed == blockedSuspendedQueue.tail)
    {
      removed->previous->next = NULL;
      blockedSuspendedQueue.tail = removed->previous;
      removed->previous = NULL;
      blockedSuspendedQueue.size--;
    }
    else
    {
      removed->previous->next = removed->next;
      removed->next->previous = removed->previous;
      removed->next = NULL;
      removed->previous = NULL;
      blockedSuspendedQueue.size--;
    }
  }

  return 0;

}
