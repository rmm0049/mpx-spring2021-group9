/**
 * @file iosched.c
 * IO Scheduler implementation
 * */

#include "dcb.h"
#include "iocb.h"
#include "ioqueue.h"
#include "iosched.h"

/**
 * Processes IO requests
 * @param int opCode, int deviceId, char *buffPtr, int *countPtr
 * @return none
 * */
void ioSchedulder(char *proc, int opCode, int deviceId, char *buffPtr, int *countPtr)
{
    if (comOne.alloc_status == AVAILABLE)
    {
        //immediately service request
    }
}
