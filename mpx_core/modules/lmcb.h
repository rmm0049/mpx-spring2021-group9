/**
 *  @file lmcb.h
 * Header file for LMCB (limited memory control block)
 */

#ifndef _LMCB_H
#define _LMCB_H

#define FREE 1
#define ALLOCATED 0

typedef struct lmcb
{
    int type; //indicated free or allocated
    int size; //indicated size in bytes of the block
} lmcb;

#endif