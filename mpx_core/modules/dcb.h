/**
 * @file dcb.h
 * Device Control Block Struct definition
 * */

#ifndef _DCB_H
#define _DCB_H

#define PIC_REG 0x20
#define PIC_EOI 0x20
#define PIC_MASK 0x21
#define IRQ_COM1 0x10
//allocation statuses
#define AVAILABLE 1
#define IN_USE 0

/*!
+enum for the possible dcb states.
*/
typedef enum status_t
{

  STATUS_IDLE,
  STATUS_READING,
  STATUS_WRITING
} status_t;

typedef struct dcb
{
    int flag;
    status_t alloc_status;
    int curr_op;
    int *event_flag;

    //user buffer descriptor
    int curr_buf_loc;         //current location of buffer
    int total_char_requested; //total request number of characters or buffer size
    int char_already_trans;   // number of characters already trasnfereed
    int *requestors_count;    //address of requestor's count variable

    //ring buffer

} dcb;

void serial_io();
int com_open(int *e_flag, int baud_rate);
void pic_mask( char enable);
void enable_interrupts();
void disable_interrupts();
#endif
