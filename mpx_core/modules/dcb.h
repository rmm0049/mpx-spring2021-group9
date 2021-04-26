/**
 * @file dcb.h
 * Device Control Block Struct definition
 * */

#ifndef _DCB_H
#define _DCB_H

//allocation statuses
#define AVAILABLE 1
#define IN_USE 0

//current operation
#define READ 0
#define WRITE 1
#define IDLE 2

typedef struct dcb
{
    int flag;
    int alloc_status;
    int curr_op;
    int *event_flag;

    //user buffer descriptor
    int curr_buf_loc;         //current location of buffer
    int total_char_requested; //total request number of characters or buffer size
    int char_already_trans;   // number of characters already trasnfereed
    int *requestors_count;    //address of requestor's count variable

    //ring buffer

} dcb;

extern dcb comPort;
void serial_io();
#endif
