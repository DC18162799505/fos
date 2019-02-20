# /kernel

# Programs, flags, etc.
ASM		    = nasm
CC		    = gcc
LD		    = ld
ASMFLAGS	= -I ../include -f elf
CFLAGS		= -Wall -c -nostdinc -fno-builtin -I../include
LDFLAGS		= -r
# This Program
OBJS		= main.o traps.o protect.o mpx386.o clock.o irq.o sched.o kernelc.o proc.o sys/sys.o
ROOT        = kernel.o
# All Phony Targets
.PHONY : everything clean

# Default starting position
everything : $(OBJS) $(ROOT)

clean :
	(rm -f $(OBJS);cd sys;make clean)

main.o : main.c 
	$(CC) $(CFLAGS) -o $@ $<
	
traps.o : traps.c
	$(CC) $(CFLAGS) -o $@ $<

protect.o : protect.c
	$(CC) $(CFLAGS) -o $@ $<

clock.o : clock.c
	$(CC) $(CFLAGS) -o $@ $<

irq.o : irq.c
	$(CC) $(CFLAGS) -o $@ $<
	
sched.o : sched.c
	$(CC) $(CFLAGS) -o $@ $<
    	
kernelc.o : kernel.c
	$(CC) $(CFLAGS) -o $@ $<

proc.o : proc.c
	$(CC) $(CFLAGS) -o $@ $<
     
sys/sys.o : 
	(cd sys;make)              
      	
mpx386.o : mpx386.asm
	$(ASM) $(ASMFLAGS) -o $@ $<
    	
kernel.o : $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)
