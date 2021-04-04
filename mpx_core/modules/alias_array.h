/**
  @file alias_array.h
  Defines the struct of the array to use for storing the alias list
*/

#ifndef _ALIAS_ARRAY_H
#define _ALIAS_ARRAY_H

typedef struct alias_array
{
  char lines[101][2][100]; //keeps track alias (0) and their text (1)
  int total; //stores current number of aliases

} alias_array;

extern alias_array aliasList;

#endif
