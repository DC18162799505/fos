# /shell

# Programs, flags, etc.
CC		    = gcc
LD		    = ld
CFLAGS		= -Wall -c -nostdinc -fno-builtin -I../include
LDFLAGS		= -r
# This Program
OBJS		= tty.o
ROOT        = shell.o
# All Phony Targets
.PHONY : everything clean

# Default starting position
everything : $(OBJS) $(ROOT)

clean :
	rm -f $(OBJS)

tty.o : tty.c
	$(CC) $(CFLAGS) -o $@ $<

shell.o : $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)
