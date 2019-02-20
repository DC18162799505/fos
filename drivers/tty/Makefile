# /drivers/tty

# Programs, flags, etc.
CC		    = gcc
LD		    = ld
CFLAGS		= -Wall -c -nostdinc -fno-builtin -I../../include
LDFLAGS		= -r
# This Program
OBJS		= keyboard.o console.o key_encode.o
ROOT        = tty.o
# All Phony Targets
.PHONY : everything clean

# Default starting position
everything : $(OBJS) $(ROOT)

clean :
	rm -f $(OBJS)

keyboard.o : keyboard.c
	$(CC) $(CFLAGS) -o $@ $<

console.o : console.c
	$(CC) $(CFLAGS) -o $@ $<

key_encode.o : key_encode.c
	$(CC) $(CFLAGS) -o $@ $<
	
tty.o : $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)
