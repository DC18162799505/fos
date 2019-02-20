# /lib/asm

# Programs, flags, etc.
ASM		    = nasm
LD		    = ld
ASMFLAGS	= -f elf
LDFLAGS		= -r
# This Program
OBJS		= ioport.o regctl.o
ROOT        = asm.o
# All Phony Targets
.PHONY : everything clean

# Default starting position
everything : $(OBJS) $(ROOT)

clean :
	rm -f $(OBJS)
	
ioport.o : ioport.asm
	$(ASM) $(ASMFLAGS) -o $@ $<

regctl.o : regctl.asm 
	$(ASM) $(ASMFLAGS) -o $@ $<

asm.o : $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)
