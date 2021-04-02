/**
 * @file memControl.c
 * Function implementation of memory control Functions
 * */

#include "memControl.h"
#include <system.h>
#include "mpx_supt.h"
#include <core/interrupts.h>
#include <mem/heap.h>
#include <string.h>
#include <core/serial.h>
#include "cmcb.h"
#include "lmcb.h"
#include "mcbList.h"

int isInit = 0;
void *memoryHeap;    //global heap variable
int memorySize;      //Size of memory
int memoryAllocated; //how much memory is allocated
cmcb *freeHead;      //reference to beginning of free list
cmcb *allocatedHead; // reference to beginning of allocated list

cmcb *placeCMCB(int size, void *pos, int type, cmcb *prev, cmcb *next)
{
    cmcb *new = (cmcb *)pos;
    new->type = type;
    new->begAddr = pos + sizeof(cmcb);
    new->size = size;
    new->memSize = size - sizeof(cmcb) - sizeof(lmcb);
    new->next = next;
    new->prev = prev;

    return new;
}

void mergeAdjacent()
{
    int doneMerging = 0;
    cmcb *node = freeHead;

    int changesMade = 0;

    while (!doneMerging)
    {
        if (node == NULL)
        {
            if (changesMade)
            {
                changesMade = 0;
                node = freeHead;
            }
            else
            {
                doneMerging = 1;
            }
        }
        else if ((void *)node + node->size == (void *)node->next)
        {
            cmcb *next = node->next->next;
            cmcb *prev = node->prev;
            int actualSize = node->size + node->next->size;
            cmcb *newFMCB = placeCMCB(actualSize, (void *)node, FREE, prev, next);
            if (prev != NULL)
            {
                prev->next = newFMCB;
            }
            if (next != NULL)
            {
                next->prev = newFMCB;
            }
            changesMade = 1;
        }
        else
        {
            node = node->next;
        }
    }
}

int initializeHeap(int size)
{
    if (size <= 0)
        return -1;

    if (!isInit) //if heap is not already Initialized
    {
        isInit = 1;
        memoryAllocated = 0;
        memorySize = size + sizeof(cmcb) + sizeof(lmcb);
        //initalizes heap
        memoryHeap = (void *)kmalloc(sizeof(cmcb) + sizeof(lmcb) + size);

        //first CMCB
        cmcb *firstCMCB = (cmcb *)memoryHeap;
        firstCMCB->type = FREE; // free
        firstCMCB->begAddr = memoryHeap + sizeof(cmcb);
        firstCMCB->size = size + sizeof(cmcb) + sizeof(lmcb);
        firstCMCB->memSize = size - sizeof(cmcb) - sizeof(lmcb);
        firstCMCB->next = NULL;
        firstCMCB->prev = NULL;
        strcpy(firstCMCB->name, "free");

        //initialize free and alloacted heads
        freeHead = firstCMCB;
        allocatedHead = NULL;

        //first LMCB
        lmcb *firstLMCB = (lmcb *)(size - sizeof(lmcb)); //might be wrong
        firstLMCB->type = FREE;
        firstLMCB->size = size + sizeof(cmcb) + sizeof(lmcb);

        return 0; //initialiation was successful
    }
    return -1; //already initialized
}

void *allocateMemory(u32int size)
{
    if (!isInit) //heap isn't initialized
    {
        println_error("Heap isn't initialized");
        return NULL;
    }
    if (size <= 0) //size is invalid
    {
        println_error("Invalid size parameter");
        return NULL;
    }
    if (memorySize - memoryAllocated < (int)(sizeof(cmcb) + sizeof(lmcb) + size))
    {
        println_error("Not enough memory left");
        return NULL;
    }
    int actualSize = sizeof(cmcb) + sizeof(lmcb) + size;

    int positionNotFound = 1;
    cmcb *freeMemList = freeHead;
    while (positionNotFound)
    {
        if (freeMemList == NULL) //end of memory, not enough space
        {
            println_error("Didn't find place");
            return NULL;
        }
        if (freeMemList->size >= actualSize) //found a spot
        {
            positionNotFound = 0; //break out of loop
        }
        else
        {
            freeMemList = freeMemList->next;
        }
    }

    //store info from new node
    cmcb *prev = freeMemList->prev;
    cmcb *next = freeMemList->next;
    void *addr = (void *)freeMemList;
    int prevSize = freeMemList->size;

    cmcb *newAlloc = placeCMCB(actualSize, addr, ALLOCATED, NULL, NULL);

    strcpy(newAlloc->name, getCOP());

    memoryAllocated += actualSize;

    //new free block that is the "leftover" needs to be reinserted into free list
    cmcb *newFree = placeCMCB(prevSize - actualSize, (void *)newAlloc + newAlloc->size, FREE, prev, next);

    //TODO - create list functions to add, remove from list
    if (prev != NULL)
    {
        prev->next = newFree;
    }
    if (next != NULL)
    {
        next->prev = newFree;
    }
    if (newFree->prev == NULL)
    {
        freeHead = newFree;
    }

    int spotFound = 0;
    if (allocatedHead == NULL)
    {
        allocatedHead = newAlloc;
        return (void *)newAlloc->begAddr;
    }
    cmcb *node = allocatedHead;
    while (!spotFound)
    {
        if (newAlloc < node)
        {
            newAlloc->next = node;
            newAlloc->prev = node->prev;
            newAlloc->prev->next = newAlloc;
            node->prev = newAlloc;
            if (allocatedHead == node)
            {
                allocatedHead = newAlloc;
            }
            spotFound = 1;
        }
        else if (node->next == NULL)
        {
            node->next = newAlloc;
            newAlloc->prev = node;
            spotFound = 1;
        }
        else
        {
            node = node->next;
        }
    }
    return (void *)newAlloc->begAddr;
}

int freeMemory(void *memoryPtr)
{
    int isFound = 0;
    cmcb *node = allocatedHead;

    while (!isFound)
    {
        if (node == NULL)
        {
            println_error("Couldn't find memory pointer");
            return 0;
        }
        if (node->begAddr == memoryPtr)
        {
            isFound = 1;
        }
        else
        {
            node = node->next;
        }
    }

    if (node == allocatedHead)
    {
        allocatedHead = allocatedHead->next;

        if (allocatedHead != NULL)
        {
            allocatedHead->prev = NULL;
        }
    }
    else
    {
        if (node->next != NULL)
        {
            node->next->prev = node->prev;
        }
        if (node->prev != NULL)
        {
            node->prev->next = node->next;
        }
    }

    cmcb *newFree = placeCMCB(node->size, (void *)node, FREE, NULL, NULL);
    memoryAllocated -= newFree->size;
    if (freeHead == NULL)
    {
        freeHead = newFree;
    }
    else
    {
        int spotFound = 0;
        cmcb *newNode = freeHead;
        while (!spotFound)
        {
            if (newFree < newNode)
            {
                newFree->prev = newNode->prev;
                newFree->next = newNode;
                newNode->prev->next = newFree;
                newNode->prev = newFree;
                spotFound = 1;
                if (newNode == freeHead)
                {
                    freeHead = newFree;
                }
            }
            else if (newNode->next == NULL)
            {
                newFree->prev = newNode;
                newNode->next = newFree;
                spotFound = 1;
            }
            else
            {
                newNode = newNode->next;
            }
        }
    }
    mergeAdjacent(); //merges adjacent free blocks of memory back together
    return 1;        //returned successful
}

cmcb *getFreeHead()
{
    return freeHead;
}

cmcb *getAllocatedHead()
{
    return allocatedHead;
}

int isEmpty()
{
    if (memoryAllocated == 0)
    {
        return 1;
    }
    return 0;
}