/**
 * @file memComm.h
 * Header file for memory control commands
 * */

#ifndef _MEM_COMM_H
#define _MEM_COMM_H

#define OFFSET 218103852

#include "cmcb.h"
/**
 * Initializes heap with given size
 * */
void initHeap(int size);

/**
 * Checks to see if heap is empty
 * */
void isEmptyComm();

/**
 * User command to allocate memory
 * @param int size
 * @return u32int pointer of block of memory
 **/
void allocateMem(int size);

/**
 * User command to free memory
 * @param pointer to the block to free
 * @return
 * */
void freeMem(void *memPtr);

/**
 * Prints to the screen all the free memory available
 * */
void showFree();

/**
 * Prints to the screen all the alloacted memory available
 * */
void showAllocated();

/**
 * Prints the given block information
 * @param cmbc* block
 * */

void printMCBInfo(cmcb *block);

#endif