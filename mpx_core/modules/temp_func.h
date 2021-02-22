/**
  @file temp_func.h
  Function definitions for temporary commands R2
*/

#ifndef _TEMP_FUNC_H
#define _TEMP_FUNC_H

/**
  Creates PCB and inserts into the appropriate queue
  @param char *params
*/

void createPCB(char *params);

/**
  Removes PCB from appropriate queue and frees all associated
  memory
  @param char *name
*/

void deletePCB(char *name);

/**
  Finds PCB and sets its stae to blocked and reinserts
  into the appropriate queue
  @param char *name
*/

void blockPCB(char *name);

/**
  Makes PCB into the unblocked state and reinserts
  into the appropriate queue
  @param char *name
*/

void unblockPCB(char *name);



#endif
