/*------------------------------------------------------------------------------
  һЩ�˿ڵĺ궨�弰����������� 
------------------------------------------------------------------------------*/

#ifndef       _IOPORT_H_
#define       _IOPORT_H_

/*-------------Bios �˿� -----------------------------------------------------*/
#define       CMOS_OUT        0x70
#define       CMOS_IN         0x71
/*-------------8259A�ж϶˿�--------------------------------------------------*/
#define       INT_M_CTL       0x20
#define       INT_M_CTLMASK   0x21
#define       INT_S_CTL       0xA0
#define       INT_S_CTLMASK   0xA1
/*-------------ʱ�Ӷ˿�-------------------------------------------------------*/
#define       TIMER0_IN     0x40
#define       TIMER1_IN     0x41
#define       TIMER2_IN     0x42
#define       TIMER_CTL_IN  0x43
/*-------------���̶˿�-------------------------------------------------------*/
/*IBM CP/ATֻ��0x60��0x64�����˿�*/
#define	KB_DATA		0x60	/* I/O port for keyboard data
					           Read : Read Output Buffer 
					           Write: Write Input Buffer(8042 Data&8048 Command) */
#define	KB_CMD		0x64	/* I/O port for keyboard command
					           Read : Read Status Register
					           Write: Write Input Buffer(8042 Command) */
/*-------------CGA�˿�--------------------------------------------------------*/
#define CRTC_ADDR             0x3D4           /*�����Ĵ���*/
#define CRTC_DATA             0x3D5           /*���ݼĴ���*/

/*-------------Ӳ�̶˿�-------------------------------------------------------*/
#define HD_DATA               0x1f0            /*���ݼĴ���*/
#define HD_ERROR              0x1f1            /*����״̬�Ĵ���*/ 
#define HD_PRECOMP            0x1f1            /*дǰԤ�����Ĵ��������ã�*/
#define HD_NSECTOR            0x1f2            /*�������Ĵ���*/ 
#define HD_SECTOR             0x1f3            /*�����żĴ���*/
#define HD_LCYL               0x1f4            /*����żĴ������ͣ�*/
#define HD_HCYL               0x1f5            /*����żĴ������ߣ�*/
#define HD_CURRENT            0x1f6            /*������/��ͷ�Ĵ��� ��101dhhhh,d=�������ţ�h��ͷ�ţ�*/
#define HD_STATUS             0x1f7            /*��״̬�Ĵ���*/
#define HD_COMMAND            0x1f7            /*����Ĵ���*/
#define HD_CMD                0x3f6            /*Ӳ�̿��ƼĴ���*/
#define HD_INPUT              0x3f7            /*��������Ĵ���*/

/*-------------���̶˿�-------------------------------------------------------*/
#define FD_DOR                0x3f2            /*�������������*/
#define FD_STATUS             0x3f4            /*FDC��״̬�Ĵ���*/
#define FD_DATA               0x3f5            /*FDC���ݼĴ���*/
#define FD_DIR                0x3f7            /* Digital Input Register (read) */
#define FD_DCR                0x3f7            /* Diskette Control Register (write)*/

/*-------------DMA�˿�--------------------------------------------------------*/
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

/*�������ݿ�Ķ�д*/
#define port_read(port,buf,nr) \
__asm__("cld;rep;insw"::"d" (port),"D" (buf),"c" (nr))

#define port_write(port,buf,nr) \
__asm__("cld;rep;outsw"::"d" (port),"S" (buf),"c" (nr))

#define sti() __asm__ ("sti"::)
#define cli() __asm__ ("cli"::)
#define nop() __asm__ ("nop"::)

#endif

/*-------------�����������---------------------------------------------------*/
int8    inb(int16);
void    outb(int16,int8);
int16   inw(int16);
void    outw(int16,int16);
