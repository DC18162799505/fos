/*-------------------------------------------------------------------------
一次加载一个扇区
-------------------------------------------------------------------------*/
#include   "type.h"
#include   "string.h"
#include   "IOPort.h"
#include   "protect.h"
#include   "regctl.h"
#include   "sys\proc.h"
#include   "sys\trap.h"
#include   "sys\irq.h"
#include   "fos\dev.h"
#include   "sys\kernel.h"
#include   "fos\fs.h"
#include   "fos\fd.h"
#include   "fos\blk.h"

/*读取控制器状态信息，如果错误，则reset = 1*/
void output_byte(char byte)
{
    int counter;
    unsigned char status;

    if (reset)
        return;
    for(counter = 0 ; counter < 10000 ; counter++) 
    {
        status = inb(FD_STATUS) & (STATUS_READY | STATUS_DIR);
        if(status == STATUS_READY) 
        {
            outb(FD_DATA,byte);
            return;
        }
    }
    reset = 1;
    printc("Unable to send byte to FDC\n");
}

/*读取FDC结果信息*/
int result(void)
{
    int i = 0, counter, status;

    if (reset)
        return -1;
    for (counter = 0 ; counter < 10000 ; counter++) 
    {
        status = inb(FD_STATUS)&(STATUS_DIR | STATUS_READY | STATUS_BUSY);
        if(status == STATUS_READY)
            return i;
        if(status == (STATUS_DIR | STATUS_READY | STATUS_BUSY)) 
        {
            if (i >= MAX_REPLIES)
                break;
            reply_buffer[i++] = inb(FD_DATA);
        }
    }
    reset = 1;
    printc("Get status times out\n");
    return -1;
}

/*初始化软盘DMA通道*/
void setup_DMA(void)
{
     long addr = (long) current_request->buffer;
     cli();
     /*缓冲区处于1M以上的需要把它拷贝进tmp_floppy_area*/
     if (addr >= 0x100000) 
     {
         addr = (long) tmp_floppy_area;
         if (command == FD_WRITE)
             copy_buffer(current_request->buffer,tmp_floppy_area);
     }
 /* mask DMA 2 */
     outb(DMA_MASK0,4|2);
 /* output command byte. */
     __asm__("outb %%al,$12\n\tjmp 1f\n1:\tjmp 1f\n1:\t"
     "outb %%al,$11\n\tjmp 1f\n1:\tjmp 1f\n1:"::
     "a" ((char) ((command == FD_READ)?DMA_READ:DMA_WRITE)));
 /* 8 low bits of addr */
     outb(DMA2_ADDR,addr);
     addr >>= 8;
 /* bits 8-15 of addr */
     outb(DMA2_ADDR,addr);
     addr >>= 8;
 /* bits 16-19 of addr */
     outb(DMA2_PAGE,addr);
 /* low 8 bits of count-1 (512-1=0x1ff) */
     outb(DMA2_COUNT,0xff);
 /* high 8 bits of count-1 */
     outb(DMA2_COUNT,1);
 /* activate DMA 2 */
     outb(DMA_MASK0,0|2);
     sti();	   
}

void bad_flp_intr(void)
{
	   current_request -> errors ++;
	   /*出错次数大于一半，则置复位标志，需对软驱进行复位操作，然后再试。否则软驱需要重新校正一下再试验*/
	   if(current_request -> errors > MAX_ERRORS / 2)
	   	    reset = 1;
	   else
	   	    recalibrate = 1;
}

void rw_interrupt(int32 irq)
{	   
     if (result() != 7 || (ST0 & 0xD8) || (ST1 & 0xbf) || (ST2 & 0x73)) 
     {
     	   printc("%d\n",ST0);
     	   printc("%d\n",ST1);
     	   printc("%d\n",ST2);   	   
     	   printc("rw failed!");
     	   
         if (ST1 & 0x02) 
         {
             printk("Drive %d is write protected\n",0);
             end_request(0);
         }
         return;
     }
     if (command == FD_READ && (unsigned long)(current_request -> buffer) >= 0x100000)
         copy_buffer(tmp_floppy_area,current_request -> buffer);
     end_request(1);
     bool_rw = 0;
}

void setup_rw_floppy(void)
{   
     setup_DMA();
     put_irq_handler(Floppy_IRQ, rw_interrupt);
     output_byte(command);
     output_byte(head << 2);
     output_byte(track);
     output_byte(head);
     output_byte(sector);
     output_byte(2);                    /* sector size = 512 */
     output_byte(18);
     output_byte(floppy_type.gap);
     output_byte(0xFF);                 /* sector size (0xff when n!=0 ?) */
     
     bool_rw = 1;
     while(bool_rw);
}

void init_interrupt(int32 irq)
{
	   return;
}
void seek_interrupt(int32 irq)
{
	   output_byte(FD_SENSEI);
     if (result() != 2 || (ST0 & 0xF8) != 0x20 || ST1 != seek_track) 
     {
         printc("seek failed!");
         return;
     }
     current_track = ST1;
     bool_seek = 0;
}

void transfer(void)
{
	   /*设置驱动器参数*/
     if (cur_spec1 != floppy_type.specl) 
     {
         cur_spec1 = floppy_type.specl;
         output_byte(FD_SPECIFY);
         output_byte(cur_spec1);     /* hut etc */
         output_byte(6);             /* Head load time =6ms, DMA */
     }
     /*设置传输速率*/
     if (cur_rate != floppy_type.rate)
         outb(FD_DCR,cur_rate = floppy_type.rate);
}

void recal_interrupt(int32 irq)
{
     output_byte(FD_SENSEI);
     if (result()!=2 || (ST0 & 0xE0) == 0x60)
         reset = 1;
     else
         recalibrate = 0;
     do_fd_request();
}

void unexpected_floppy_interrupt(int32 irq)
{
     output_byte(FD_SENSEI);
     if (result()!=2 || (ST0 & 0xE0) == 0x60)
         reset = 1;
     else
         recalibrate = 1;	   
}

void recalibrate_floppy(void)
{
     recalibrate = 0;
     current_track = 0;
     fd_handler = recal_interrupt;
     output_byte(FD_RECALIBRATE);
     output_byte(head<<2 | 0);
     if (reset)
         do_fd_request();	   
}

void reset_interrupt(int32 irq)
{
     output_byte(FD_SENSEI);
     (void) result();
     output_byte(FD_SPECIFY);
     output_byte(cur_spec1);     /* hut etc */
     output_byte(6);         /* Head load time =6ms, DMA */
     do_fd_request();	   
}

void reset_floppy(void)
{
	   int i;
	   
     reset = 0;
     cur_spec1 = -1;
     cur_rate = -1;
     recalibrate = 1;
     printk("Reset-floppy called\n");
     cli();
     fd_handler = reset_interrupt;
     outb(FD_DOR,current_DOR & ~0x04);
     for (i=0 ; i<100 ; i++)
         __asm__("nop");
     outb(FD_DOR,current_DOR);
     sti();	   
}

void seek_floppy()
{
	   seek = 0;
	   current_track = seek_track;
	   
	   put_irq_handler(Floppy_IRQ, seek_interrupt);
     if (seek_track) 
     {
         output_byte(FD_SEEK);
         output_byte(head<<2);
         output_byte(seek_track);
     } 
     else 
     {
         output_byte(FD_RECALIBRATE);
         output_byte(head<<2);
     }
     
     bool_seek = 1;
     while(bool_seek);     
}
/*开启软盘并处理好传输速率*/
void floppy_on(void)
{
	   int i,j;
	   
     selected = 1;

     /*开启软启A*/
     current_DOR = 0x1C;
     
     outb(FD_DOR,current_DOR);
     
     /*延时*/
     for(i = 0;i < 1000;i ++)
         for(j = 0;j < 1000;j ++)
             ;
             
     transfer();
}

/*软盘请求读写处理函数*/
void do_fd_request()
{
	   int i;
     unsigned int block;

     seek = 0;
     if (reset) 
     {
         reset_floppy();
         return;
     }
     if (recalibrate) 
     {
         recalibrate_floppy();
         return;
     }
     /*判断请求项是否为空*/
     if(current_request == NULL)
     	   return;

     block = current_request -> bh -> sector;
     
     if (block >= floppy_type.size) 
     {
         end_request(0);
         printk("fd.c:overflow floppy_type.size!");
     }
     
     /*磁头号，柱面号和起始扇区号的计算*/
     sector = block % floppy_type.sect + 1;                      /*起始扇区*/
     block /= floppy_type.sect;
     head = block % floppy_type.head;                            /*磁头号*/
     track = block / floppy_type.head;                           /*柱面号*/
     
     seek_track = track << floppy_type.stretch;                  /*在1.44M中floppy_type.stretch = 0*/
     
     if (seek_track != current_track)
         seek = 1;
     if (current_request->cmd == READ)
         command = FD_READ;
     else if (current_request->cmd == WRITE)
         command = FD_WRITE;
     else
         printk("do_fd_request: unknown command");
     
     if(seek)
     	   seek_floppy();
     	   
     setup_rw_floppy();
}

void init_fd()
{
	   recalibrate = 0;
	   reset       = 0;
	   seek        = 0;
	   
	   cur_spec1 = -1;
     cur_rate = -1;
     sector = 0;
     head = 0;
     track = 0;
     seek_track = 0;
     current_track = 255;
     command = 0;
     selected = 0;
	   
	   /*1.44MB软盘*/
	   floppy_type.size    = 2880;
	   floppy_type.sect    = 18;
	   floppy_type.head    = 2;
	   floppy_type.track   = 80;
	   floppy_type.stretch = 0;
	   floppy_type.gap     = 0x1B;
	   floppy_type.rate    = 0x00;
	   floppy_type.specl   = 0xCF;
	   
	   put_irq_handler(Floppy_IRQ, init_interrupt);
	   Enable_irq(Floppy_IRQ);                          /* 开启软盘中断*/  	    
	   floppy_on(); 
}
