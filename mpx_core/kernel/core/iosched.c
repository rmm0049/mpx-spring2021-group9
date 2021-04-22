/**
 * @file iosched.c
 * IO Scheduler implementation
 * */

/**
 * Processes IO requests
 * @param int opCode, int deviceId, char *buffPtr, int *countPtr
 * @return none
 * */

#include <modules/dcb.h>
#include "modules/iocb.h"
#include "modules/queue.h"

void ioSchedulder(char *proc, int opCode, int deviceId, char *buffPtr, int *countPtr)
{
    // if device is not busy
    //     immediately service with
    //     com_read or com_write
    // otherwise
    //     place rquest in queue
}
