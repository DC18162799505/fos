# /kernel/sys

# Programs, flags, etc.
ASM		    = nasm
CC		    = gcc
LD		    = ld
ASMFLAGS	= -I ../../include -f elf
CFLAGS		= -Wall -c -nostdinc -fno-builtin -I../../include
LDFLAGS		= -r
# This Program
OBJS		= sys_write.o sys_call.o sys_fork.o sys_execve.o
ROOT        = sys.o
# All Phony Targets
.PHONY : everything clean

# Default starting position
everything : $(OBJS) $(ROOT)

clean :
	rm -f $(OBJS)

sys_write.o : sys_write.c 
	$(CC) $(CFLAGS) -o $@ $<
    	
sys_call.o  : sys_call.c
	$(CC) $(CFLAGS) -o $@ $<

sys_fork.o : sys_fork.c
	$(CC) $(CFLAGS) -o $@ $<

sys_execve.o : sys_execve.c
	$(CC) $(CFLAGS) -o $@ $<
		
sys.o : $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)
