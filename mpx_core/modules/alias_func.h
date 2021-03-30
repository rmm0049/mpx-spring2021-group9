/**
  @file alias_func.h
  Defines all of the alias operation functions as
  internal procedures
*/

#ifndef _ALIAS_FUNC_H
#define _ALIAS_FUNC_H

#include "alias_array.h"

/**
  checks if Alias List is currently empty
  returns 1 if empty, 0 otherwise
*/

int isAliasListEmpty();

/**
  adds an alias to the alias list
  @param char *alias, char *aliastext
*/

void addAlias(char *alias,char *aliastext);

/**
  identifies if param is an alias, if it is, change input buffer
  @param char *buffer
*/

void identifyAlias(char *buffer);


#endif
