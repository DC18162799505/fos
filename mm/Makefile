# /mm

# Programs, flags, etc.
CC		    = gcc
LD		    = ld
CFLAGS		= -Wall -c -nostdinc -fno-builtin -I../include
LDFLAGS		= -r
# This Program
OBJS		= memory.o
ROOT        = mm.o
# All Phony Targets
.PHONY : everything clean

# Default starting position
everything : $(OBJS) $(ROOT)

clean :
	rm -f $(OBJS)

memory.o : memory.c
	$(CC) $(CFLAGS) -o $@ $<
	    	
mm.o : $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)
