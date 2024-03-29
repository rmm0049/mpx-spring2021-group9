/**
  @file serial.c

  Contains methods and variables used for
    serial input and output.
*/

#include <stdint.h>
#include <string.h>

#include <core/io.h>
#include <core/serial.h>
#include "modules/mpx_supt.h"
#include "modules/chl_array.h"
#include "modules/chl_func.h"
#define NO_ERROR 0

/// Active devices used for serial output
int serial_port_out = 0;
/// Active devices used for serial output
int serial_port_in = 0;

int i = 0; //!< counter for polling
/**
  @brief Initializes serial device
  @param int device
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

/**
    Writes a message to the active serial output device.
    Appends a newline character.
    @param const char *msg
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

/**

  Writes a message to the active serial output device.
    @param const char *msg
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

/*int (*student_read)(char *buffer, int *count); */

/**
    Sets serial_port_out to the given device address.
    All serial output, such as that from serial_println, will be
    directed to this device.
    @param int device
*/
int set_serial_out(int device)
{
  serial_port_out = device;
  return NO_ERROR;
}

/**

   Sets serial_port_in to the given device address.
    All serial input, such as console input via a virtual machine,
    QEMU/Bochs/etc, will be directed to this device.
    @param int device
*/
int set_serial_in(int device)
{
  serial_port_in = device;
  return NO_ERROR;
}


///Keepts track of the cursor position in the terminal
int cursor=0;
/**
  Repeatedly checks status register to see if a bit
  has been entered, stores and prints, or does another action to the input.
  @param: char *buffer, int *count
*/

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
          addCHL(buffer);      //add buffer to command history
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

          serial_print("\x1B[u"); //restores cursor position
          serial_print("\x1B[1D"); //moves cursor one to the left to account for the character backspaced

        }//end backspace if



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

          if (ch3 == 65){ // up arrow
            if(history.currenti>0){
              //clear current line, buffer and reset cursor
              //{}

              for(j=cursor; j>=1; j--){
                serial_print("\x1B[1D"); //sets the cursor to the beginning of the line
                *(buffer+j-1)='\0'; //clears buffer
              }

              serial_print("\x1B[K"); //clears the line
              cursor = 0; i =0;// resets cursor variable


              history.currenti--;
              //history.lines[history.currenti]
              //print current line, store new buffer, set cursor
              serial_print(history.lines[history.currenti]);
              int leng;
              for(leng = 0; leng<strlen(history.lines[history.currenti]);leng++){
                *(buffer+leng)=history.lines[history.currenti][leng];
                cursor++;
                i++;
              }

            }
          }

          else if (ch3 == 66){ //down arrow
            if(history.currenti<history.nexti){
              //clear current line, buffer and reset cursor
              //{}
              for(j=cursor; j>=1; j--){
                serial_print("\x1B[1D"); //sets the cursor to the beginning of the line
                *(buffer+j-1)='\0'; //clears buffer
              }

              serial_print("\x1B[K"); //clears the line
              cursor = 0; i =0;// resets cursor variable

              history.currenti++;
              if(history.currenti<history.nexti){
                //print current line, store new buffer, set cursor
                serial_print(history.lines[history.currenti]);
                int leng;
                for(leng = 0; leng<strlen(history.lines[history.currenti]);leng++){
                  *(buffer+leng)=history.lines[history.currenti][leng];
                  cursor++;
                  i++;
                }
              }
            }
          }

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
            if (i != cursor){ //doesn't allow user to go past the length of string
              serial_print("\x1B[1C"); //move to right
              cursor++;
            }
          }

        }
      }
      else if (i != cursor)
      {

        serial_print("\x1B[s"); //saves the current cursor position
        int k;
        for (k = i; k >= cursor; k--)
        {
            *(buffer+k+1) = *(buffer+k);
        }

        *(buffer+cursor) = ch; //makes the character to the right the typed char

        for(j=cursor; j>=1; j--){
          serial_print("\x1B[1D"); //sets the cursor to the beginning of the line
        }

        serial_print("\x1B[K"); //clears the line

        serial_print(buffer);
        i++; //increment size of buffer
        (*count)--; //decrement how many characters left in buffer to fill
        cursor++;


        serial_print("\x1B[u"); //restores cursor position
        serial_print("\x1B[1C"); //moves cursor one to the right to account for the character added

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

/**
  Prints the message in error color red
  @param char *msg
*/

void println_error(char *msg){ //this method is used to set the color of the error messages to red
  simple_print(RED); //set the text color to red
  simple_print(msg); //print the text
  simple_print("\n");
  simple_print(DEFAULT); //set the text color to the default color
}

/**
  Prints the message in warning color yellow
  @param char *msg
*/

void println_warning(char *msg){ //this method is used to set the color of the warning messages to yellow
  simple_print(YELLOW); //set the color of the text to yellow
  simple_print(msg); //print the text
  simple_print("\n");
  simple_print(DEFAULT); //set the text color to the default color
}

/**
  Prints the message in confirmation color green with newline
  @param char *msg
*/

void println_confirmation(char *msg){ //this method is used to set the color of the confirmation messages to green
  simple_print(GREEN); //set the text color to green
  simple_print(msg);
  simple_print("\n"); //print the text
  simple_print(DEFAULT); //set the text color to the default color
}

/**
  Prints the message in confirmation color green
  @param char *msg
*/

void print_confirmation(char *msg){ //this method is used to set the color of the confirmation messages to green
  simple_print(GREEN); //set the text color to green
  simple_print(msg); //print the text
  simple_print(DEFAULT); //set the text color to the default color
}

/**
  Prints the message in default color and newline
  @param char *msg
*/

void println_message(char *msg){
  simple_print(msg);
  simple_print("\n");
}

/**
  Prints the message out to the screen
  @param char *msg
*/

void simple_print(char *msg){
  int count = strlen(msg);
  sys_req(WRITE, COM1, msg, &count);

}
