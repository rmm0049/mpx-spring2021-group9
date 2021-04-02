/**
 * @file cmcbList.h
 * Definition of MCB list to contain MCBs
 * */

#ifndef _MCB_LIST_H
#define _MCB_LIST_H

#include "cmcb.h"

typedef struct mcbList
{
    int size;   //size of the list
    cmcb *head; //pointer to the head of list
    cmcb *tail; //pointer to the tail of list
} mcbList;

extern mcbList freeList;
extern mcbList allocatedList;

#endif