/**
  @file pcb.h
  Defines the PCB (Process Control Block) struct
*/

#ifndef _PCB_H
#define _PCB_H

#include <string.h>

#define STACK_SIZE 1024

///type of process
#define APPLICATION_P 1
#define SYSTEM_P 0

//state of process
#define READY 0
#define RUNNING 1
#define BLOCKED 2

//suspended status
#define SUSPSEND 1
#define NOT_SUSP 0


typedef struct pcb
{
  char name[20]; //name of the process
  int class; //1 for application, 0 for system??
  int priority; //0-9 to show priority 0-low 9-high

  //two state variables
  int state; //ready, running, blocked (1,2,3)
  int suspended; //1 - suspended 0 - not suspended

  unsigned char stack[STACK_SIZE]; //stack array
  unsigned char *topStack;
  unsigned char *baseStack;

  struct pcb *next; //points to the next PCB
  struct pcb *previous; //points to previous PCB

} pcb;


#endif
