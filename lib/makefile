# /lib

# Programs, flags, etc.
CC		    = gcc
LD		    = ld
CFLAGS		= -Wall -c -nostdinc -fno-builtin -I../include
LDFLAGS		= -r
# This Program
OBJS		= string.o asm/asm.o syscall/syscall.o klib.o regctl.o
ROOT        = lib.o
# All Phony Targets
.PHONY : everything clean clean_main clean_asm clean_syscall

# Default starting position
everything : $(OBJS) $(ROOT)

clean : clean_main clean_asm clean_syscall

clean_main :
	rm -f $(OBJS)

clean_asm :
	(cd asm;make clean)	

clean_syscall :
	(cd syscall;make clean)
              
string.o : string.c
	$(CC) $(CFLAGS) -o $@ $<
	
klib.o : klib.c
	$(CC) $(CFLAGS) -o $@ $<

regctl.o : regctl.c
	$(CC) $(CFLAGS) -o $@ $<
    	
asm/asm.o : 
	(cd asm;make)
	
syscall/syscall.o :
	(cd syscall;make)
        	
lib.o : $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)
