/*
  ----- serial.c -----

  Description..: Contains methods and variables used for
    serial input and output.
*/

#include <stdint.h>
#include <string.h>

#include <core/io.h>
#include <core/serial.h>

#define NO_ERROR 0

// Active devices used for serial I/O
int serial_port_out = 0;
int serial_port_in = 0;

int i = 0; // counter for polling
/*
  Procedure..: init_serial
  Description..: Initializes devices for user interaction, logging, ...
*/
int init_serial(int device)
{
  outb(device + 1, 0x00); //disable interrupts
  outb(device + 3, 0x80); //set line control register
  outb(device + 0, 115200/9600); //set bsd least sig bit
  outb(device + 1, 0x00); //brd most significant bit
  outb(device + 3, 0x03); //lock divisor; 8bits, no parity, one stop
  outb(device + 2, 0xC7); //enable fifo, clear, 14byte threshold
  outb(device + 4, 0x0B); //enable interrupts, rts/dsr set
  (void)inb(device);      //read bit to reset port
  return NO_ERROR;
}

/*
  Procedure..: serial_println
  Description..: Writes a message to the active serial output device.
    Appends a newline character.
*/
int serial_println(const char *msg)
{
  int i;
  for(i=0; *(i+msg)!='\0'; i++){
    outb(serial_port_out,*(i+msg));
  }
  outb(serial_port_out,'\r');
  outb(serial_port_out,'\n');
  return NO_ERROR;
}

/*
  Procedure..: serial_print
  Description..: Writes a message to the active serial output device.
*/
int serial_print(const char *msg)
{
  int i;
  for(i=0; *(i+msg)!='\0'; i++){
    outb(serial_port_out,*(i+msg));
  }
  if (*msg == '\r') outb(serial_port_out,'\n');
  return NO_ERROR;
}

/*int (*student_read)(char *buffer, int *count);
  Procedure..: set_serial_out
  Description..: Sets serial_port_out to the given device address.
    All serial output, such as that from serial_println, will be
    directed to this device.
*/
int set_serial_out(int device)
{
  serial_port_out = device;
  return NO_ERROR;
}

/*
  Procedure..: set_serial_in
  Description..: Sets serial_port_in to the given device address.
    All serial input, such as console input via a virtual machine,
    QEMU/Bochs/etc, will be directed to this device.
*/
int set_serial_in(int device)
{
  serial_port_in = device;
  return NO_ERROR;
}

/*
  Procedure..: int *polling
  Description..: Repeatedly checks status register to see if a bit
  has been entered, stores and prints, or does another action to the input.
  Params: char *buffer, int *count
*/
int cursor=0;

int *polling(char *buffer, int *count){
//  must validate each key and handle special keys such as delete, back space, and
// arrow keys

  int i = 0;
  int j = 0;
  cursor = 0;
  serial_print("$ ");
  while (1 & ((*count) > 0))
  {
    if (inb(COM1+5) & 1)
    {
      const unsigned char ch = inb(COM1);
      *(buffer+i) = ch; //store character in buffer array
      serial_print(buffer+i); //print the character to the screen
      i++; //increment counter
      cursor++; //increment cursor 
      (*count)--; //decreases buffer count

      //enter case
      if (ch == '\r'){ //checks if enter key has been entered
        *(buffer+i) = '\0';   //append a null character to output after return
        return 0;
      }

      //delete case
      if (ch == 127){ //checks if backspace key has been entered
        serial_print("\x1B[s"); //saves the current cursor position
        *(buffer+cursor) = '@'; //replaces the character with a deletion marker

        for(j=cursor; j<1; j--){
          serial_print("\x1B[1D"); //sets the cursor to the beginning of the line
        }

        serial_print("\x1B[K"); //clears the line

        int m=0;
        for(j=0; j == i; j++){ //goes through the buffer
          if(*(buffer+j) != '@'){ //if the character isn't the deletion marker,
            serial_print(buffer+j); //print the character in the buffer

          }

        }

        serial_print("\x1B[u"); //restores cursor position
        serial_print("\x1B[1D"); //moves cursor one to the left to account for the character backspaced

      }
      //still need implementation of backspace, delete, arrow keys, and buffer size
      if(ch == 224){
        const unsigned char ch2 = inb(COM1);
        if(ch2 == 115){ //checks if left arrow has been entered
          if(cursor == 0){
            serial_print("\x1B[1C");
          }
          else{
            cursor--;
          }
        }
        if(ch2 == 116){ //checks if the right arrow has been entered
          cursor++;

        }
      }

    }
  }

  return count;
}
