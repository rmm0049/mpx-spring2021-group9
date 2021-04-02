/**
 * @file mcbList.c
 * Contains the lists for free and allocated mcbs
 * */
#include "mcbList.h"

mcbList freeList = {0, NULL, NULL};
mcbList allocatedList = {0, NULL, NULL};