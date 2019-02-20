# /drivers/floppy

# Programs, flags, etc.
CC		    = gcc
LD		    = ld
CFLAGS		= -Wall -c -nostdinc -fno-builtin -I../../include
LDFLAGS		= -r
# This Program
OBJS		= fd.o blk.o
ROOT        = floppy.o
# All Phony Targets
.PHONY : everything clean

# Default starting position
everything : $(OBJS) $(ROOT)

clean :
	rm -f $(OBJS)

fd.o : fd.c
	$(CC) $(CFLAGS) -o $@ $<

blk.o : blk.c
	$(CC) $(CFLAGS) -o $@ $<
		
floppy.o : $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)
