/**
  @file loadcomhand.c
  Loads comhand() as a process
*/

#include "loadcomhand.h"
#include <core/context.h>
#include <core/serial.h>
#include "pcb.h"
#include "temp_func.h"
#include "pcb_func.h"
#include "perm_pcb_comm.h"
#include "comhand.h"
#include "mpx_supt.h"
#include <string.h>
#include <system.h>

void loadComhand()
{
  pcb *comhand = setupPCB("comhand", 0, 9);
  context *cp = (context *)(comhand->topStack);
  memset(cp, 0, sizeof(context));

  //set register values
  cp->fs = 0x10;
  cp->gs = 0x10;
  cp->ds = 0x10;
  cp->es = 0x10;
  cp->cs = 0x08;
  cp->ebp = (u32int)comhand->stack;
  cp->esp = (u32int)comhand->topStack;
  cp->eip = (u32int)comhandler;
  cp->eflags = 0x202;

  insertPCB(comhand);
}

void loadIdle()
{
  pcb *idlepcb = setupPCB("idle", 0, 0);
  context *cp = (context *)(idlepcb->topStack);
  memset(cp, 0, sizeof(context));

  //set register values
  cp->fs = 0x10;
  cp->gs = 0x10;
  cp->ds = 0x10;
  cp->es = 0x10;
  cp->cs = 0x08;
  cp->ebp = (u32int)idlepcb->stack;
  cp->esp = (u32int)idlepcb->topStack;
  cp->eip = (u32int)idle;
  cp->eflags = 0x202;

  insertPCB(idlepcb);
}

void loadInfinite()
{
  pcb *infinite = setupPCB("infinite", 1, 0);
  context *cp = (context *)(infinite->topStack);
  memset(cp, 0, sizeof(infinite));

  //set register values
  cp->fs = 0x10;
  cp->gs = 0x10;
  cp->ds = 0x10;
  cp->es = 0x10;
  cp->cs = 0x08;
  cp->ebp = (u32int)infinite->stack;
  cp->esp = (u32int)infinite->topStack;
  cp->eip = (u32int)infiniteProc;
  cp->eflags = 0x202;

  insertPCB(infinite);
}

void infiniteProc()
{
  while (1)
  {
    //println_message("Infinite Proc Ran");
    sys_req(IDLE, COM1, NULL, NULL);
  }
}
