#include       "type.h"
#include       "IOPort.h"
#include       "string.h"
#include       "sys\trap.h"
#include       "fos\memory.h"
#include       "fos\keyboard.h"
#include       "fos\console.h"
#include       "fos\tty.h"

void set_cursor(int32 position)
{
	cli();
	outb(CRTC_ADDR, Cursor_h);
	outb(CRTC_DATA, (position >> 8) & 0xFF);
	outb(CRTC_ADDR, Cursor_l);
	outb(CRTC_DATA, position & 0xFF);
	sti();
}

void set_video(int32 addr)
{
	cli();
	outb(CRTC_ADDR, Addr_start_h);
	outb(CRTC_DATA, (addr >> 8) & 0xFF);
	outb(CRTC_ADDR, Addr_start_l);
	outb(CRTC_DATA, addr & 0xFF);
	sti();
}

void   flush_console(struct Tty *tty)
{
       set_cursor(tty->console.cursor);
       set_video(current_tty->console.original_addr); 
}

void   console_output(int32 ch,struct Tty *tty)
{
       tty->console.console_mem[tty->console.cursor * 2] = (int8)ch;
       tty->console.console_mem[tty->console.cursor * 2 + 1] = 0x0F;
       tty->console.cursor ++;
       if(tty->console.cursor >= tty->console.v_mem_limit)
            scroll_console(tty);
       flush_console(tty);
}

void scroll_console(struct Tty *tty)
{
     int32 i;
     for(i = tty->console.original_addr * 2;i < tty->console.original_addr * 2 + 3840;i ++)
           tty->console.console_mem[i] = tty->console.console_mem[i + 160];
     for(i = tty->console.original_addr * 2 + 3840;i < tty->console.original_addr * 2 + 4000;i += 2)
           tty->console.console_mem[i] = ' ';
     tty->console.cursor -= 80;
}
