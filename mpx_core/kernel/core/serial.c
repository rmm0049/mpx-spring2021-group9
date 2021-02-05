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
  int m = 0;
  cursor = 0;
  serial_print("$ ");
  while (1 & ((*count) > 0))
  {
    if (inb(COM1+5) & 1)
    {
      const unsigned char ch = inb(COM1);

      //enter case
      if (ch == '\r'){ //checks if enter key has been entered
        if (i != 0)
        {
          *(buffer+i) = '\0';  //append a null character to output after return
        }
        else *(buffer) = '\r';

        serial_print("\r");
        return 0;
      }

      //delete case
      else if (ch == 127){ //checks if backspace key has been entered
        serial_print("\x1B[s"); //saves the current cursor position
        if (cursor != 0)
        {
          *(buffer+cursor-1) = '@'; //replaces the character with a deletion marker

          for(j=cursor; j>=1; j--){
            serial_print("\x1B[1D"); //sets the cursor to the beginning of the line
          }

          cursor--; //decrement cursor

          serial_print("\x1B[K"); //clears the line


          for(j=0; j <= i; j++){ //goes through the buffer
            if(*(buffer+j) != '@'){ //if the character isn't the deletion marker,
              *(buffer+m) = *(buffer+j);
              m++;
            }
            else {

              *(buffer+m) = '\0';
            }

          }
          serial_print(buffer);
          i--; //decrement size of buffer
          (*count)++; //increment how many characters left in buffer to fill
          m = 0;

        }//end backspace if

         serial_print("\x1B[u"); //restores cursor position
         serial_print("\x1B[1D"); //moves cursor one to the left to account for the character backspaced

      }

      else if(ch == 27){
        const unsigned char ch2 = inb(COM1);
        if(ch2 == 91){ //checks if an arrow key or delete was pressed
          const unsigned char ch3 = inb(COM1); //gets third character

          if (ch3 == 51) //delete character
          {
            const unsigned char ch4 = inb(COM1); //gets fourth character
            if (ch4 == 126)
            {
              //Where delete does it's stuff
              serial_print("\x1B[s"); //saves the current cursor position
              *(buffer+cursor) = '@'; //makes the character to the right @

              for(j=cursor; j>=1; j--){
                serial_print("\x1B[1D"); //sets the cursor to the beginning of the line
              }

               serial_print("\x1B[K"); //clears the line

               for(j=0; j <= i; j++){ //goes through the buffer
                 if(*(buffer+j) != '@'){ //if the character isn't the deletion marker,
                   *(buffer+m) = *(buffer+j);
                   m++;
                 }
                 else {

                   *(buffer+m) = '\0';
                 }

               }
               
               serial_print(buffer);
               i--; //decrement size of buffer
               (*count)++; //increment how many characters left in buffer to fill
               m = 0;

               serial_print("\x1B[u"); //restores cursor position
            }
          }

          if (ch3 == 65); // Down arrow don't do anything

          else if (ch3 == 66); //Up arrow don't do anything

          else if (ch3 == 68) //left arrow
          {
              if (cursor != 0) //if cursor is 0 don't go past $
              {
                serial_print("\x1B[1D"); //move to left
                cursor--;
              }

          }
          else if (ch3 == 67) //right arrow
          {
            serial_print("\x1B[1C"); //move to right
            cursor++;
          }

        }
      }
      else {
        *(buffer+i) = ch; //store character in buffer array
        serial_print(buffer+i); //print the character to the screen
        i++; //increment counter
        cursor++; //increment cursor
        (*count)--; //decreases buffer count
      }

    }
  }

  return count;
}
