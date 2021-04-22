/**
 * @file iocb.h
 * struct definition of IOCB data structure
 * */

#ifndef _IOCB_H
#define _IOCB_H

#include "pcb.h"
#include "dcb.h"

typedef struct iocb
{

    pcb *proc;
    dcb *device;
    int operation;
    char buffer[50];
    int count;

} iocb;

#endif