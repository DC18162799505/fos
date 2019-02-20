# /test

# Programs, flags, etc.
DASM		  = ndisasm
ASM		    = nasm
CC		    = gcc
LD		    = ld
DASMFLAGS = -b32
ASMFLAGS	= -f elf
CFLAGS		= -c -fno-builtin -I../include
LDFLAGS		= -s -r -N -m elf_i386 -Ttext 0x0
OBJ       = objcopy
OBJFLAGS  = -O binary -R .note -R .comment
# This Program
OBJS		= test0.o test1.o
ROOT        = test0.map test1.map
# All Phony Targets
.PHONY : everything clean

# Default starting position
everything : $(OBJS) $(ROOT) test0.bin test1.bin

clean :
	rm -f $(OBJS) $(ROOT) test0.bin test1.bin

disasm :
	($(DASM) $(DASMFLAGS) test0.bin > in0.txt;$(DASM) $(DASMFLAGS) test1.bin > in1.txt)
	
test0.o : test0.c
	$(CC) $(CFLAGS) -o $@ $<

test1.o : test1.c
	$(CC) $(CFLAGS) -o $@ $<
	
test0.map : test0.o
	$(LD) $(LDFLAGS) -o $@ $<

test1.map : test1.o
	$(LD) $(LDFLAGS) -o $@ $<
	
test0.bin : test0.map
	$(OBJ) $(OBJFLAGS) $< $@

test1.bin : test1.map
	$(OBJ) $(OBJFLAGS) $< $@