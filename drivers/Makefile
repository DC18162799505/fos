# /drivers

# Programs, flags, etc.
CC		    = gcc
LD		    = ld
CFLAGS		= -Wall -c -nostdinc -fno-builtin -I../include
LDFLAGS		= -r
# This Program
OBJS		= tty/tty.o floppy/floppy.o
ROOT        = drivers.o
# All Phony Targets
.PHONY : everything clean clean_tty clean_floppy clean_main

# Default starting position
everything : $(OBJS) $(ROOT)

clean : clean_main clean_tty clean_floppy

clean_main : 
	(rm -f $(OBJS))	
	
clean_tty :
	(cd tty;make clean)	
    
clean_floppy : 
	(cd floppy;make clean)
                                 
tty/tty.o : 
	(cd tty;make)

floppy/floppy.o :
	(cd floppy;make)            
      
drivers.o : $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)
