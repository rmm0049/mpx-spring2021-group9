/**
  @file alias_func.c
  Implementation of internal alias functions
*/

#include "alias_func.h"
#include "alias_array.h"
#include "mpx_supt.h"
#include <string.h>
#include <core/serial.h>
#define MAX_HISTORY 100
#define ALIAS 0
#define ALIASEDTEXT 1


/**
  checks if Alias List is currently empty
  returns 1 if empty, 0 otherwise
*/

int isAliasListEmpty(){
  if (aliasList.total == 0){
    return 1;
  }
    return 0;
}

/**
  adds an alias to the alias list
  @param char *alias, char *aliastext
*/
void addAlias(char *alias,char *aliastext)
{
  if(isAliasListEmpty()){
    strcpy(aliasList.lines[0][ALIAS],alias);
    strcpy(aliasList.lines[0][ALIASEDTEXT],aliastext);
    aliasList.total++;
  }
  else if(aliasList.total<MAX_HISTORY){//list has at least one entry
    int match = 0;
    int i = 0;
    for(i = 0;i<aliasList.total;i++){
      int maxBufferSize = (strlen(alias)>(strlen(aliasList.lines[i][ALIAS]))) ? (strlen(alias)):(strlen(aliasList.lines[i][ALIAS]));
      if (strncmp(alias,aliasList.lines[i][ALIAS],maxBufferSize) == 0){
        //change the aliased text for the matching alias
        strcpy(aliasList.lines[i][ALIASEDTEXT], aliastext);
        match = 1; //match was found
      }
    }
    if (!match){//if no match was found, add at end of list
      strcpy(aliasList.lines[aliasList.total][ALIAS],alias);
      strcpy(aliasList.lines[aliasList.total][ALIASEDTEXT],aliastext);
      aliasList.total++;
    }

  }
  if(aliasList.total==MAX_HISTORY){//list is too large, reset
    aliasList.total=0;
  }
  return;
}

/**
  identifies if param is an alias, if it is, change input buffer
  @param char *buffer
*/

void identifyAlias(char *buffer){
  int i = 0;
  for(i = 0;i<aliasList.total;i++){
    int maxBufferSize = (strlen(buffer)>(strlen(aliasList.lines[i][ALIAS]))) ? (strlen(buffer)):(strlen(aliasList.lines[i][ALIAS]));
    if(strncmp(buffer,aliasList.lines[i][ALIAS],maxBufferSize) == 0){
      strcpy(buffer, aliasList.lines[i][ALIASEDTEXT]);
      return;
    }
  }
  return;
}
