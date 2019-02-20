# /drivers/harddisk

# Programs, flags, etc.
CC		    = gcc
LD		    = ld
CFLAGS		= -Wall -c -nostdinc -fno-builtin -I../../include
LDFLAGS		= -r
# This Program
OBJS		= hd.o blk.o
ROOT        = harddisk.o
# All Phony Targets
.PHONY : everything clean

# Default starting position
everything : $(OBJS) $(ROOT)

clean :
	rm -f $(OBJS)

hd.o : hd.c
	$(CC) $(CFLAGS) -o $@ $<

blk.o : blk.c
	$(CC) $(CFLAGS) -o $@ $<
	
harddisk.o : $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)
