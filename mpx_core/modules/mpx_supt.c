/*************************************************************
*	This C file contains the MPX support functions
*	which will be used through out the semester, many set
*	flags or methods that will allow us to modify
*	The behavior of MPX as it progresses throughout
* 	the semester.
**************************************************************/

/**
	@file mpx_supt.c
	contains the MPX support functions
*/

#include "mpx_supt.h"
#include <mem/heap.h>
#include <string.h>
#include <core/serial.h>

/// global variable containing parameter used when making system calls via sys_req
param params;

/// global for the current module
int current_module = -1;
static int io_module_active = 0;
static int mem_module_active = 0;

// If a student created heap manager is implemented this
// is a pointer to the student's "malloc" operation.
u32int (*student_malloc)(u32int);

// if a student created heap manager is implemented this
// is a pointer to the student's "free" operation.
int (*student_free)(void *);

/**
*	This function is use to issue system requests
*	for service.
*
*	@param int op_code, int device_id, char *buffer_ptr, int *count_ptr
*/

int sys_req(int op_code,
            int device_id,
            char *buffer_ptr,
            int *count_ptr)

{
  int return_code = 0;

  if (op_code == IDLE || op_code == EXIT)
  {
    // store the process's operation request
    // triger interrupt 60h to invoke
    params.op_code = op_code;
    asm volatile("int $60");
  } // idle or exit

  else if (op_code == READ || op_code == WRITE)
  {
    // validate buffer pointer and count pointer
    if (buffer_ptr == NULL)
      return_code = INVALID_BUFFER;
    else if (count_ptr == NULL || *count_ptr <= 0)
    { //Don't know why this is messing
      // return_code = INVALID_COUNT; //up the sys_req WRITE call becasue
      //it thinks the count_ptr is NULL when it's not???
    }

    // if parameters are valid store in the params structure
    if (return_code == 0)
    {
      params.op_code = op_code;
      params.device_id = device_id;
      params.buffer_ptr = buffer_ptr;
      params.count_ptr = count_ptr;

      if (!io_module_active)
      {
        // if default device
        if (op_code == READ)
          return_code = *(polling(buffer_ptr, count_ptr));

        else
        { //must be WRITE
          return_code = serial_print(buffer_ptr);
        }
      }
      else
      { // I/O module is implemented
        asm volatile("int $60");
      } // NOT IO_MODULE
    }
  }
  else
    return_code = INVALID_OPERATION;

  return return_code;
} // end of sys_req

/**
  	Initialize MPX support software, based
			on the current module.  The operation of
			MPX will changed based on the module selected.
			THIS must be called as the first executable
			statement inside your command handler.

  @param int cur_mod
*/
void mpx_init(int cur_mod)
{

  current_module = cur_mod;
  if (cur_mod == MEM_MODULE)
    mem_module_active = TRUE;

  if (cur_mod == IO_MODULE)
    io_module_active = TRUE;
}

/**
  Sets the memory allocation function for sys_alloc_mem
	@param Function pointer
*/
void sys_set_malloc(u32int (*func)(u32int))
{
  student_malloc = func;
}

/**
  Sets the memory free function for sys_free_mem
  @param  s1-destination, s2-source
*/
void sys_set_free(int (*func)(void *))
{
  student_free = func;
}

/**
   Allocates a block of memory (similar to malloc)
  @param u32int size
*/
void *sys_alloc_mem(u32int size)
{
  if (!mem_module_active)
    return (void *)kmalloc(size);
  else
    return (void *)(*student_malloc)(size);
}

/**
  Frees memory
  @param void *ptr
*/
int sys_free_mem(void *ptr)
{
  if (mem_module_active)
    return (*student_free)(ptr);
  // otherwise we don't free anything
  return -1;
}

/**
   The idle process, used in dispatching
			it will only be dispatched if NO other
			processes are available to execute.
*/
void idle()
{
  // char msg[30];
  // int count = 0;

  // memset(msg, '\0', sizeof(msg));
  // strcpy(msg, "IDLE PROCESS EXECUTING.\n");
  // count = strlen(msg);

  while (1)
  {
    //sys_req(WRITE, DEFAULT_DEVICE, msg, &count);
    sys_req(IDLE, DEFAULT_DEVICE, NULL, NULL);
  }
}

int getMemModule()
{
  return mem_module_active;
}
