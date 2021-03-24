/**
 * @file memControl.h
 * Header file for memory control functions
 * */

#ifndef _MEM_CONTROL_H
#define _MEM_CONTROL_H

#include <system.h>
#include "cmcb.h"

/**
 * Creates a new cmcb struct and places accordingly
 * @param int size, void *pos, int type, cmcb *prev, cmcb *next
 * */

cmcb *placeCMCB(int size, void *pos, int type, cmcb *prev, cmcb *next);
/**
 * initializes heap with a given size
 * @param int size
 * @return int 0 or 1 if successful or not
 * */
int initializeHeap(int size);

/**
 * Allocates a block of memory with the given size
 * @param int size
 * */
void *allocateMemory(u32int size);

/**
 * Frees a block of memory from the heap
 * @param void* to the block
 * @return int - 0 or 1 if successful or note
 * */
int freeMemory(void *memoryPtr);

/**
 * Returns true or false if the heap is empty
 * @return true or false
 * */
int isEmpty();

/**
 * Merges adjacent blocks of free memory together
 * @return none
 * */

void mergeAdjacent();

/**
 * Gets the free list head pointer
 * @return cmcb *
 * */

cmcb *getFreeHead();

/**
 * Gets the allocated list head pointer
 * @return cmcb *
 * */
cmcb *getAllocatedHead();

#endif