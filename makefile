# /main makefile

# Programs, flags, etc.
DASM		= ndisasm
LD		    = ld
LDFLAGS		= -s -N -m elf_i386 -Ttext 0 
OBJ         = objcopy
OBJFLAGS    = -O binary -R .note -R .comment 
DASMFLAGS   = -b32
# This Program
OBJS		= boot/head.o kernel/kernel.o lib/lib.o mm/mm.o drivers/drivers.o shell/shell.o fs/fs.o
ROOT        = kernel.o kernel.bin
# All Phony Targets
.PHONY : everything clean clean_main clean_boot clean_kernel clean_lib buildimg disasm clean_drivers clean_shell clean_test clean_fs

# Default starting position
everything : $(OBJS) $(ROOT) test/test.o

# Write "boot.bin" & "loader.bin" into floppy image "TINIX.IMG"
# We assume that "TINIX.IMG" exists in current folder
buildimg :
	mount FOS.IMG /mnt/floppy -o loop
	cp -f boot/loader.bin /mnt/floppy/
	cp -f kernel.bin /mnt/floppy
	cp -f test/test0.bin /mnt/floppy
	cp -f test/test1.bin /mnt/floppy
	umount  /mnt/floppy
	
disasm :
	$(DASM) $(DASMFLAGS) kernel.bin > in.txt
    	
clean : clean_main clean_kernel clean_lib clean_mm clean_drivers clean_shell clean_test clean_fs

clean_main:
	(rm -f $(OBJS);rm -f kernel.o)  
	    
clean_kernel:
	(cd kernel;make clean)
	
clean_lib:     
	(cd lib;make clean)

clean_mm:     
	(cd mm;make clean)
                          
clean_drivers:
	(cd drivers;make clean)
	
clean_shell:	
	(cd shell;make clean)

clean_test:
	(cd test;make clean)

clean_fs:
	(cd fs;make clean)           
	    	
boot/head.o : 
	(cd boot;make)	

kernel/kernel.o : 
	(cd kernel;make)	
	
lib/lib.o : 
	(cd lib;make)	

mm/mm.o :
	(cd mm;make)

drivers/drivers.o:
	(cd drivers;make)

shell/shell.o:
	(cd shell;make)

test/test.o :
	(cd test;make)

fs/fs.o :
	(cd fs;make)  
             	
kernel.o : $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

kernel.bin : kernel.o
	$(OBJ) $(OBJFLAGS) $< $@
