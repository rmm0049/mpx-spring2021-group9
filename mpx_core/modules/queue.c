/**
  @file queue.c
  Defines global queues of read, ready-suspended,
  blocked, and blocked-suspended
*/

#include "queue.h"

queue readyQueue = {0, 0, 0};
queue readySuspendedQueue = {0, 0, 0};
queue blockedQueue = {0, 0, 0};
queue blockedSuspendedQueue = {0, 0, 0};
queue ioQueue = {0, 0, 0};