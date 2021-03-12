#
# Makefile for MPX Modules

AS      = nasm
CC      = i386-elf-gcc
CFLAGS  = -Wall -Wextra -Werror -nostartfiles -nostdlib -nodefaultlibs -ffreestanding -g -c
LD      = i386-elf-ld
LDFLAGS =
ASFLAGS = -f elf -g

# add new files as you create them.
# I'll start you off with just mpx_supt.o
OBJFILES =\
mpx_supt.o\
comhand.o\
version.o\
help.o\
gettime.o\
getdate.o\
settime.o\
setdate.o\
pcb_func.o\
queue.o\
commands.o\
temp_func.o\
perm_pcb_comm.o\
loadr3.o\
chl_array.o\
chl_func.o\
loadcomhand.o\
alarm.o\
alarmList.o

.c.s:
	$(CC) $(CFLAGS) -S -o $@ $<
.s.o:
	$(AS) $(ASFLAGS) -o $@ $<
.c.o:
	$(CC) $(CFLAGS) -I../include -o $@ $<\

all: modules.o

modules.o: $(OBJFILES)
	$(LD) -r -o modules.o $(OBJFILES)

clean:
	rm modules.o $(OBJFILES)
