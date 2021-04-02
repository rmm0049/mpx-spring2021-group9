/**
 * @file memComm.c
 * function implementation of user memory commands
 * */

#include "memComm.h"
//#include "mcbList.c"
#include "cmcb.h"
#include <string.h>
#include <system.h>
#include <core/serial.h>
#include "memControl.h"

void initHeap(int size)
{
    initializeHeap(size);
}

void allocateMem(int size)
{
    allocateMemory((u32int)size);
}

void freeMem(void *memPtr)
{
    freeMemory(memPtr);
}

void isEmptyComm()
{
    int value = isEmpty();
    if (value)
        println_error("Heap is empty!");
    else
        println_warning("Heap is NOT empty");
}

void showFree()
{
    cmcb *freeBlocks = getFreeHead();
    if (!(freeBlocks == NULL))
    {
        while (freeBlocks != NULL)
        {
            printMCBInfo(freeBlocks);
            freeBlocks = freeBlocks->next;
        }
    }
}

void showAllocated()
{
    cmcb *allocatedBlocks = getAllocatedHead();

    while (allocatedBlocks != NULL)
    {
        printMCBInfo(allocatedBlocks);
        allocatedBlocks = allocatedBlocks->next;
    }
}

void printMCBInfo(cmcb *block)
{
    char typeString[10];
    char addr[50];
    char size[11];

    itoa((int)(block->begAddr - OFFSET), addr, 10);
    itoa(block->memSize, size, 10);

    if (block->type == 1)
        strcpy(typeString, "free");
    else
        strcpy(typeString, "allocated");

    println_message("----------------------------");
    // simple_print("MCB name: ");
    // println_confirmation(block->name);
    simple_print("MCB Type: ");
    println_confirmation(typeString);
    simple_print("Beginning address: ");
    println_confirmation(addr);
    simple_print("Block Size: ");
    println_confirmation(size);
    println_message("----------------------------");
}