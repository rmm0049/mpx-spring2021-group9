/**
  @file queue.c
  Defines global queues of read, ready-suspended,
  blocked, and blocked-suspended
*/

#include "queue.h"

queue readyQueue = {0, NULL, NULL};
queue readySuspendedQueue = {0, NULL, NULL};
queue blockedQueue = {0, NULL, NULL};
queue blockedSuspendedQueue = {0, NULL, NULL};
