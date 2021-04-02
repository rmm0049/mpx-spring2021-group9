/**
 *  @file cmcb.h
 * Header file for CMCB (complete memory control block)
 */

#ifndef _CMCB_H
#define _CMCB_H

#include <system.h>

#define FREE 1
#define ALLOCATED 0

/**
 * Struct definition of CMCB
 * */
typedef struct cmcb
{
    int type;          //free or allocated
    int size;          //indicating size of block in bytes
    int memSize;       //size of actual block
    char name[20];     //name of PCB housed in block
    void *begAddr;     //Beginning address of block
    struct cmcb *next; //pointer to next of same type
    struct cmcb *prev; //pointer to prev of same type
} cmcb;

#endif
