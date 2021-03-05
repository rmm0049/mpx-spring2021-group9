/**
  @file loadr3.c
  Function Implementation of R3 processes
*/

#include "loadr3.h"
#include "procsr3.c"
#include "temp_func.h"
#include "pcb_func.h"
#include "perm_pcb_comm.h"
#include "pcb.h"
#include <core/context.h>


void loadproc()
{
  //pcb creations
  // createPCB("create PCB system proc1 1");
  // createPCB("create PCB application proc2 2");
  // createPCB("create PCB system proc3 3");
  // createPCB("create PCB application proc4 4");
  // createPCB("create PCB system proc5 5");

  //pcb pointers
  pcb *pcb1 = setupPCB("proc1", 1, 1);
  pcb *pcb2 = setupPCB("proc2", 1, 2);
  pcb *pcb3 = setupPCB("proc3", 1, 3);
  pcb *pcb4 = setupPCB("proc4", 1, 4);
  pcb *pcb5 = setupPCB("proc5", 1, 5);

  //context creations
  context *cp1 = (context *) (pcb1->topStack);
  context *cp2 = (context *) (pcb2->topStack);
  context *cp3 = (context *) (pcb3->topStack);
  context *cp4 = (context *) (pcb4->topStack);
  context *cp5 = (context *) (pcb5->topStack);

  //memset initializations
  memset(cp1, 0, sizeof(context));
  memset(cp2, 0, sizeof(context));
  memset(cp3, 0, sizeof(context));
  memset(cp4, 0, sizeof(context));
  memset(cp5, 0, sizeof(context));

  //register initializations
  cp1->fs = 0x10;
  cp1->gs = 0x10;
  cp1->ds = 0x10;
  cp1->es = 0x10;
  cp1->cs = 0x08;
  cp1->ebp = (u32int) pcb1->stack;
  cp1->esp = (u32int) pcb1->topStack;
  cp1->eip = (u32int) proc1;
  cp1->eflags = 0x202;

  cp2->fs = 0x10;
  cp2->gs = 0x10;
  cp2->ds = 0x10;
  cp2->es = 0x10;
  cp2->cs = 0x08;
  cp2->ebp = (u32int) pcb2->stack;
  cp2->esp = (u32int) pcb2->topStack;
  cp2->eip = (u32int) proc2;
  cp2->eflags = 0x202;

  cp3->fs = 0x10;
  cp3->gs = 0x10;
  cp3->ds = 0x10;
  cp3->es = 0x10;
  cp3->cs = 0x08;
  cp3->ebp = (u32int) pcb3->stack;
  cp3->esp = (u32int) pcb3->topStack;
  cp3->eip = (u32int) proc3;
  cp3->eflags = 0x202;

  cp4->fs = 0x10;
  cp4->gs = 0x10;
  cp4->ds = 0x10;
  cp4->es = 0x10;
  cp4->cs = 0x08;
  cp4->ebp = (u32int) pcb4->stack;
  cp4->esp = (u32int) pcb4->topStack;
  cp4->eip = (u32int) proc4;
  cp4->eflags = 0x202;

  cp5->fs = 0x10;
  cp5->gs = 0x10;
  cp5->ds = 0x10;
  cp5->es = 0x10;
  cp5->cs = 0x08;
  cp5->ebp = (u32int) pcb5->stack;
  cp5->esp = (u32int) pcb5->topStack;
  cp5->eip = (u32int) proc5;
  cp5->eflags = 0x202;

  //put PCBs into suspended state
  pcb1->suspended = SUSPSEND;
  pcb2->suspended = SUSPSEND;
  pcb3->suspended = SUSPSEND;
  pcb4->suspended = SUSPSEND;
  pcb5->suspended = SUSPSEND;

  insertPCB(pcb1);
  insertPCB(pcb2);
  insertPCB(pcb3);
  insertPCB(pcb4);
  insertPCB(pcb5);

}
