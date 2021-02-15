/**
  @file queue.c
  Defines global queues of read, ready-suspended,
  blocked, and blocked-suspended
*/

#include "queue.h"

struct queue readyQueue;
struct queue readySuspendedQueue;
struct queue blockedQueue;
struct queue blockedSuspendedQueue;
