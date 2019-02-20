#include "type.h"
#include "string.h"
#include "protect.h"
#include "regctl.h"
#include "IOPort.h"
#include "fos\memory.h"
#include "sys\trap.h"
#include "sys\irq.h"
#include "fos\keyboard.h"
#include "fos\keymap.h"
#include "fos\console.h"
#include "fos\tty.h"

void kb_wait()	/* 等待 8042 的输入缓冲区空 */
{
	int8 kb_stat;

	do
    {
		kb_stat = inb(KB_CMD);
	} while (kb_stat & 0x02);
}

void kb_ack()
{
	int8 kb_read;

	do 
    {
		kb_read = inb(KB_DATA);
	} while (kb_read =! KB_ACK);
}

void set_leds()
{
	int8 leds = (caps_lock << 2) | (num_lock << 1) | scroll_lock;

	kb_wait();
	outb(KB_DATA, LED_CODE);
	kb_ack();

	kb_wait();
	outb(KB_DATA, leds);
	kb_ack();
}

int8 buff_read_keyboard()
{
    int8 scan_code;
    
    while(Key_buff.counts <= 0);
    
    cli();
    scan_code = Key_buff.buffer[Key_buff.p_start ++];
    Key_buff.p_start %= NR_KEY;
    Key_buff.counts --;
    sti();
    
    return scan_code;
}

void keyboard_handler(int irq)
{
     int8  scan_code;
     
     scan_code = inb(KB_DATA);
     if(Key_buff.counts < NR_KEY)
     {
           Key_buff.buffer[Key_buff.p_end ++] = scan_code;
           Key_buff.p_end %= NR_KEY;
           Key_buff.counts ++;
     }
}

void key_init()
{
		code_with_E0 = 0;
		shift_l = 0;		         /* l shift state	*/
		shift_r = 0;		         /* r shift state	*/
		alt_l = 0;	    		     /* l alt state		*/
		alt_r = 0;		             /* r alt state	    */
		ctrl_l = 0;			         /* l ctrl state	*/
		ctrl_r = 0;			         /* r ctrl state	*/
		caps_lock = 0;		         /* Caps Lock		*/
		num_lock = 1;		         /* Num Lock		*/
		scroll_lock = 0;	         /* Scroll Lock		*/
		
		set_leds();
		
	    put_irq_handler(Keyboard_IRQ, keyboard_handler);	/* 设定键盘中断处理程序 */
	    Enable_irq(Keyboard_IRQ);				/* 开键盘中断 */		
}
int32 keyboard_read()
{
    int     i;
	int8	scan_code;
	int32	make = 0;	
	int32	key = 0;
    int32   *keyrow;
    int32   column;
    int32   caps;
    
	if(Key_buff.counts > 0)
    {
		code_with_E0 = 0;
		scan_code = buff_read_keyboard();

		/* 下面开始解析扫描码 */
		if (scan_code == 0xE1) 
        {
			for(i=1;i<6;i++)
				buff_read_keyboard;
            key = PAUSEBREAK;

		}
		else if (scan_code == 0xE0) {
			code_with_E0 = 1;
			scan_code = buff_read_keyboard();

			/* PrintScreen 被按下 */
			if (scan_code == 0x2A) 
            {
                key = PRINTSCREEN;
				code_with_E0 = 0;
				buff_read_keyboard();
				buff_read_keyboard();
				make = 1;
			}
			/* PrintScreen 被释放 */
			else if (scan_code == 0xB7) 
            {
                key = PRINTSCREEN;
				code_with_E0 = 0;
				buff_read_keyboard();
				buff_read_keyboard();
				make = 0;
			}
		} 
		if ((key != PAUSEBREAK) && (key != PRINTSCREEN)) 
        {
			make = (scan_code & Flag_break ? 0 : 1);
			
			keyrow = &keymap[(scan_code & 0x7F) * MAP_COLS];

			column = 0;

			caps = shift_l || shift_r;
			if (caps_lock) 
            {
				if ((keyrow[0] >= 'a') && (keyrow[0] <= 'z')){
					caps = !caps;
				}
			}
			if (caps) 
				column = 1;

			if (code_with_E0) 
				column = 2;

			key = keyrow[column];

			switch(key) 
            {
			case SHIFT_L:
				shift_l	= make;
				break;
			case SHIFT_R:
				shift_r	= make;
				break;
			case CTRL_L:
				ctrl_l	= make;
				break;
			case CTRL_R:
				ctrl_r	= make;
				break;
			case ALT_L:
				alt_l	= make;
				break;
			case ALT_R:
				alt_l	= make;
				break;
			case CAPS_LOCK:
				if (make) 
                {
					caps_lock   = !caps_lock;
					set_leds();
				}
				break;
			case NUM_LOCK:
				if (make) 
                {
					num_lock    = !num_lock;
					set_leds();
				}
				break;
			case SCROLL_LOCK:
				if (make) 
                {
					scroll_lock = !scroll_lock;
					set_leds();
				}
				break;
			default:
				break;
			}
		}

		if(make)
        {
            key_receive(key);
		}
	}
    return 0;
}
