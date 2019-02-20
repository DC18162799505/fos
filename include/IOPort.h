/*------------------------------------------------------------------------------
  一些端口的宏定义及输入输出函数 
------------------------------------------------------------------------------*/

#ifndef       _IOPORT_H_
#define       _IOPORT_H_

/*-------------Bios 端口 -----------------------------------------------------*/
#define       CMOS_OUT        0x70
#define       CMOS_IN         0x71
/*-------------8259A中断端口--------------------------------------------------*/
#define       INT_M_CTL       0x20
#define       INT_M_CTLMASK   0x21
#define       INT_S_CTL       0xA0
#define       INT_S_CTLMASK   0xA1
/*-------------时钟端口-------------------------------------------------------*/
#define       TIMER0_IN     0x40
#define       TIMER1_IN     0x41
#define       TIMER2_IN     0x42
#define       TIMER_CTL_IN  0x43
/*-------------键盘端口-------------------------------------------------------*/
/*IBM CP/AT只有0x60和0x64两个端口*/
#define	KB_DATA		0x60	/* I/O port for keyboard data
					           Read : Read Output Buffer 
					           Write: Write Input Buffer(8042 Data&8048 Command) */
#define	KB_CMD		0x64	/* I/O port for keyboard command
					           Read : Read Status Register
					           Write: Write Input Buffer(8042 Command) */
/*-------------CGA端口--------------------------------------------------------*/
#define CRTC_ADDR             0x3D4           /*索引寄存器*/
#define CRTC_DATA             0x3D5           /*数据寄存器*/

/*-------------硬盘端口-------------------------------------------------------*/
#define HD_DATA               0x1f0            /*数据寄存器*/
#define HD_ERROR              0x1f1            /*错误状态寄存器*/ 
#define HD_PRECOMP            0x1f1            /*写前预补偿寄存器（不用）*/
#define HD_NSECTOR            0x1f2            /*扇区数寄存器*/ 
#define HD_SECTOR             0x1f3            /*扇区号寄存器*/
#define HD_LCYL               0x1f4            /*柱面号寄存器（低）*/
#define HD_HCYL               0x1f5            /*柱面号寄存器（高）*/
#define HD_CURRENT            0x1f6            /*驱动器/磁头寄存器 （101dhhhh,d=驱动器号，h磁头号）*/
#define HD_STATUS             0x1f7            /*主状态寄存器*/
#define HD_COMMAND            0x1f7            /*命令寄存器*/
#define HD_CMD                0x3f6            /*硬盘控制寄存器*/
#define HD_INPUT              0x3f7            /*数字输入寄存器*/

/*-------------软盘端口-------------------------------------------------------*/
#define FD_DOR                0x3f2            /*数字输出控制器*/
#define FD_STATUS             0x3f4            /*FDC主状态寄存器*/
#define FD_DATA               0x3f5            /*FDC数据寄存器*/
#define FD_DIR                0x3f7            /* Digital Input Register (read) */
#define FD_DCR                0x3f7            /* Diskette Control Register (write)*/

/*-------------DMA端口--------------------------------------------------------*/
#define DMA0_PAGE             0x87
#define DMA0_ADDR             0x00
#define DMA0_COUNT            0x01

#define DMA1_PAGE             0x83
#define DMA1_ADDR             0x02
#define DMA1_COUNT            0x03

#define DMA2_PAGE             0x81
#define DMA2_ADDR             0x04
#define DMA2_COUNT            0x05

#define DMA3_PAGE             0x82
#define DMA3_ADDR             0x06
#define DMA3_COUNT            0x07

#define DMA4_PAGE             0x8F
#define DMA4_ADDR             0xC0
#define DMA4_COUNT            0xC2

#define DMA5_PAGE             0x8B
#define DMA5_ADDR             0xC4
#define DMA5_COUNT            0xC6

#define DMA6_PAGE             0x89
#define DMA6_ADDR             0xC8
#define DMA6_COUNT            0xCA

#define DMA7_PAGE             0x8A
#define DMA7_ADDR             0xCC
#define DMA7_COUNT            0xCE

#define DMA_CTL0              0x08
#define DMA_CTL1              0xD0
#define DMA_REQ0              0x09
#define DMA_REQ1              0xD2
#define DMA_MASK0             0x0A
#define DMA_MASK1             0xD4
#define DMA_RULE0             0x0B
#define DMA_RULE1             0xD6
#define DMA_TRIG0             0x0C
#define DMA_RTIG1             0xD8

/* DMA commands */
#define DMA_READ        0x46
#define DMA_WRITE       0x4A

/*用于数据块的读写*/
#define port_read(port,buf,nr) \
__asm__("cld;rep;insw"::"d" (port),"D" (buf),"c" (nr))

#define port_write(port,buf,nr) \
__asm__("cld;rep;outsw"::"d" (port),"S" (buf),"c" (nr))

#define sti() __asm__ ("sti"::)
#define cli() __asm__ ("cli"::)
#define nop() __asm__ ("nop"::)

#endif

/*-------------输入输出函数---------------------------------------------------*/
int8    inb(int16);
void    outb(int16,int8);
int16   inw(int16);
void    outw(int16,int16);
