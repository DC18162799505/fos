# /lib/syscall

# Programs, flags, etc.
ASM		    = nasm
CC		    = gcc
LD		    = ld
ASMFLAGS	= -f elf
CFLAGS		= -Wall -c -nostdinc -fno-builtin -I../../include
LDFLAGS		= -r
# This Program
OBJS		= write.o fork.o execve.o
ROOT        = syscall.o
# All Phony Targets
.PHONY : everything clean

# Default starting position
everything : $(OBJS) $(ROOT)

clean :
	rm -f $(OBJS)
	
write.o : write.asm
	$(ASM) $(ASMFLAGS) -o $@ $<
	
fork.o : fork.c
	$(CC) $(CFLAGS) -o $@ $<
	
execve.o : execve.asm
	$(ASM) $(ASMFLAGS) -o $@ $<

syscall.o : $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)
