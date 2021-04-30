/**
 * @file ioched.h
 * Header file for IO scheduler
 * */

#ifndef _IOSCHED_H
#define _IOSCHED_H

void ioScheduler(char *proc, int opCode, int deviceId, char *buffPtr, int *countPtr);

#endif