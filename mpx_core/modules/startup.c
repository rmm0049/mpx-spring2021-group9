/**
 * @file startup.c
 * Prints startup screen at startup
 * */

#include "startup.h"
#include "gettime.h"
#include "getdate.h"
#include <core/serial.h>
#include <system.h>
#include <core/io.h>

void printStartup()
{

    serial_println(STARTUP);

    // //gets current second
    outb(0x70, 0x00);
    int sec = (int)inb(0x71);
    int sec_dec = BCDToDecimal(sec);

    //variables + offset of time
    int offsetSec = sec_dec + 5;
    // if (offsetSec >= 60)
    // {
    //     offsetSec = offsetSec % 60;
    // }
    int i = sec_dec;
    simple_print("Loading");
    while (sec_dec < offsetSec)
    {

        // //gets current second
        outb(0x70, 0x00);
        sec = (int)inb(0x71);
        sec_dec = BCDToDecimal(sec);

        if (sec_dec > i)
        {
            simple_print(".");
            i = sec_dec;
        }
    }
    simple_print("\x1b[2J");
    simple_print("\x1b[0;0f");

    return;
}