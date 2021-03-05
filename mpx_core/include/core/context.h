/**
  @file context.h
  Defines the struct context
*/

#ifndef _CONTEXT_H
#define _CONTEXT_H

#include <system.h>

/**

*/
typedef struct context {
  u32int gs, fs, es, ds;
  u32int edi, esi, ebp, esp, ebx, edx, ecx, eax;
  u32int eip, cs, eflags;
} context;


#endif
