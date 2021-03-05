/**
  @file queue.h
  Defines the struct of a queue to use for storing the Command History
*/

#ifndef _CHL_ARRAY_H
#define _CHL_ARRAY_H

typedef struct chl_array
{
  char lines[101][100]; //keeps track of amount in queue
  int nexti;//keeps track of next index to store a line
  int currenti;//keeps track of current index when cycling

} chl_array;

extern chl_array history;

#endif
