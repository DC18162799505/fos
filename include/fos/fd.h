#ifndef       _FD_H_
#define       _FD_H_

/* Bits of main status register */
#define STATUS_BUSYMASK 0x0F        /* drive busy mask */
#define STATUS_BUSY     0x10        /* FDC busy */
#define STATUS_DMA      0x20        /* 0- DMA mode */
#define STATUS_DIR      0x40        /* 0- cpu->fdc */
#define STATUS_READY    0x80        /* Data reg ready */

/* Bits of FD_ST0 */
#define ST0_DS          0x03        /* drive select mask */
#define ST0_HA          0x04        /* Head (Address) */
#define ST0_NR          0x08        /* Not Ready */
#define ST0_ECE         0x10        /* Equipment chech error */
#define ST0_SE          0x20        /* Seek end */
#define ST0_INTR        0xC0        /* Interrupt code mask */

/* Bits of FD_ST1 */
#define ST1_MAM         0x01        /* Missing Address Mark */
#define ST1_WP          0x02        /* Write Protect */
#define ST1_ND          0x04        /* No Data - unreadable */
#define ST1_OR          0x10        /* OverRun */
#define ST1_CRC         0x20        /* CRC error in data or addr */
#define ST1_EOC         0x80        /* End Of Cylinder */

/* Bits of FD_ST2 */
#define ST2_MAM         0x01        /* Missing Addess Mark (again) */
#define ST2_BC          0x02        /* Bad Cylinder */
#define ST2_SNS         0x04        /* Scan Not Satisfied */
#define ST2_SEH         0x08        /* Scan Equal Hit */
#define ST2_WC          0x10        /* Wrong Cylinder */
#define ST2_CRC         0x20        /* CRC error in data field */
#define ST2_CM          0x40        /* Control Mark = deleted */

/* Bits of FD_ST3 */
#define ST3_HA          0x04        /* Head (Address) */
#define ST3_TZ          0x10        /* Track Zero signal (1=track 0) */
#define ST3_WP          0x40        /* Write Protect */

/* Values for FD_COMMAND */
#define FD_RECALIBRATE  0x07        /* move to track 0 */
#define FD_SEEK         0x0F        /* seek track */
#define FD_READ         0xE6        /* read with MT, MFM, SKip deleted */
#define FD_WRITE        0xC5        /* write with MT, MFM */
#define FD_SENSEI       0x08        /* Sense Interrupt Status */
#define FD_SPECIFY      0x03        /* specify HUT etc */

/* 软驱类型*/
#define FD_A            0x0
#define FD_B            0x1
#define FD_C            0x2
#define FD_D            0x3

/* 获取软驱类型*/
#define FD_DRIVE(x)     ((x) & 0x03)

/* 最多的错误次数*/
#define MAX_ERRORS      8

/* FDC变量*/
#define MAX_REPLIES     7
#define ST0             reply_buffer[0]
#define ST1             reply_buffer[1]
#define ST2             reply_buffer[2]
#define ST3             reply_buffer[3]

/* 软盘结构*/
struct floppy_struct
{
	  int32   size;                      /* 大小(扇区数)*/
	  int32   sect;                      /* 每磁道扇区数*/
	  int32   head;                      /* 磁头数*/
	  int32   track;                     /* 磁道数*/
	  int32   stretch;                   /* 对磁道是否要特殊处理(标志)*/
	  int8    gap;                       /* 扇区间隙长度(字节数)*/
	  int8    rate;                      /* 数据传输速率*/
	  int8    specl;                     /* 参数(高4位步进速率，低4位磁头卸载时间)*/
};

/*复制数据缓冲区*/
#define copy_buffer(from,to) \
__asm__("cld ; rep ; movsl" \
    ::"c" (512),"S" ((long)(from)),"D" ((long)(to)) \
    )

#endif

int recalibrate;                       /* 标志1：表示需要重新校正词头位置*/
int reset;                             /* 标志1：表示需要复位操作*/
int seek;                              /* 标志1：表示需要执行寻道操作*/

int cur_spec1;
int cur_rate;
unsigned char sector;
unsigned char head;
unsigned char track;
unsigned char seek_track;
unsigned char current_track;
unsigned char command;
unsigned char selected;

int bool_seek;
int bool_rw;

int8 current_DOR;                      /* 软盘状态*/

int8 reply_buffer[MAX_REPLIES];        /* 软盘状态信息缓冲区*/
char tmp_floppy_area[1024];            /* 软盘数据缓冲区*/

struct floppy_struct floppy_type;
   
void   (*fd_handler)(int32 irq);       /* 中断处理函数指针*/

extern void output_byte(char byte);
extern int result(void);
extern void setup_DMA(void);
extern void bad_flp_intr(void);
extern void rw_interrupt(int32 irq);
extern void setup_rw_floppy(void);
extern void init_interrupt(int32 irq);
extern void seek_interrupt(int32 irq);
extern void transfer(void);
extern void recal_interrupt(int32 irq);
extern void unexpected_floppy_interrupt(int32 irq);
extern void recalibrate_floppy(void);
extern void reset_interrupt(int32 irq);
extern void reset_floppy(void);
extern void seek_floppy(void);
extern void floppy_on(void);
extern void do_fd_request();
extern void init_fd();
