# /fs

# Programs, flags, etc.
CC		    = gcc
LD		    = ld
CFLAGS		= -Wall -c -nostdinc -fno-builtin -I../include
LDFLAGS		= -r
# This Program
OBJS		= file.o
ROOT    = fs.o
# All Phony Targets
.PHONY : everything clean

# Default starting position
everything : $(OBJS) $(ROOT)

clean : 
	(rm -f $(OBJS))	
          
file.o : file.c
	$(CC) $(CFLAGS) -o $@ $<
                 
fs.o : $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)
