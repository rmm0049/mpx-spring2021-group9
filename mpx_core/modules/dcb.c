#include "dcb.h"
void serial_io(){

}
int com_open(int *e_flag, int baud_rate){
  int device = COM1;
  comPort.alloc_status = STATUS_IDLE; //the port is idle
  comPort.event_flag = e_flag;

  outb(device + 1, 0x00); //disable interrupts
  outb(device + 3, 0x80); //set line control register
  outb(device + 0, 115200/9600); //set bsd least sig bit
  outb(device + 1, 0x00); //brd most significant bit
  outb(device + 3, 0x03); //lock divisor; 8bits, no parity, one stop
  outb(device + 2, 0xC7); //enable fifo, clear, 14byte threshold
  outb(device + 4, 0x0B); //enable interrupts, rts/dsr set
  (void)inb(device);      //read bit to reset port
  return 0;

}
void pic_mask( char enable){
  if (enable){
    int mask;
	  disable_interrupts();
	  mask = inb(PIC_MASK);
	  mask = mask & ~IRQ_COM1; //this enables inturrepts for COM1 in PIC
	  outb(PIC_MASK, mask);
	  enable_interrupts();
  }else{
    int mask;
	  disable_interrupts();
	  mask = inb(PIC_MASK);
	  mask = mask | IRQ_COM1; //this disables inturrepts for COM1 in PIC
	  outb(PIC_MASK, mask);
	  enable_interrupts();
  }
}
void enable_interrupts(){
  outb(COM1 + 1, 0x0B); // link to information: lammertbies.nl
}
void disable_interrupts(){
  outb(COM1 + 1, 0);
}
