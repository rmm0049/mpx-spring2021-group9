/**
  @file chl_func.c
  Implementation of internal chl functions
*/

#include "chl_func.h"
#include "chl_array.h"
#include "mpx_supt.h"
#include <string.h>
#include <core/serial.h>
#define MAX_HISTORY 100


void addCHL(char buffer[])
{
  if(history.nexti==0){//command history is empty
    strcpy(history.lines[0],buffer);
    history.nexti++;
    history.currenti=history.nexti;
  }
  else if(history.nexti<MAX_HISTORY){//command history has at least one entry
    int maxBufferSize = (strlen(history.lines[history.nexti-1])>(strlen(buffer))) ? (strlen(history.lines[history.nexti-1])):(strlen(buffer));
    if(strncmp(buffer,history.lines[history.nexti-1],maxBufferSize)){// check if command buffer is the same as the most recent stored in history
      strcpy(history.lines[history.nexti],buffer);
      history.nexti++;
      history.currenti=history.nexti;
    }
  }
  if(history.nexti==MAX_HISTORY){//command history is too large, reset nexti and currenti
    history.nexti=0;
    history.currenti=0;
  }
}
/**


void dispCHL(int index){

}
*/
