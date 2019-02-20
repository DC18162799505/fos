# /boot

# Programs, flags, etc.
ASM		    = nasm
LD		    = ld
ASMBFLAGS	= -I include
ASMKFLAGS	= -I include -f elf

# This Program
FOSBOOT	    = boot.bin loader.bin
FOSKERNEL	= head.o

# All Phony Targets
.PHONY : everything 

# Default starting position
everything : $(FOSBOOT) $(FOSKERNEL)

boot.bin : boot.asm include/real.inc include/fat12.asm include/string.asm include/video.asm
	$(ASM) $(ASMBFLAGS) -o $@ $<

loader.bin : loader.asm include/real.inc include/bios.asm include/string.asm include/video.asm\
               include/desmacro.asm include/klib.asm
	$(ASM) $(ASMBFLAGS) -o $@ $<

head.o : head.asm include/protect.inc include/video.asm include/desmacro.asm include/klib.asm
	$(ASM) $(ASMKFLAGS) -o $@ $<
