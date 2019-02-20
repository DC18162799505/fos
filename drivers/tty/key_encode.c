#include "type.h"
#include "string.h"
#include "protect.h"
#include "regctl.h"
#include "IOPort.h"
#include "fos\memory.h"
#include "sys\trap.h"
#include "sys\irq.h"
#include "fos\keyboard.h"
#include "fos\console.h"
#include "fos\tty.h"

void Enter_key(struct Tty *tty)
{
     tty->console.cursor = ((tty->console.cursor - tty->console.original_addr)/ 80 + 1) * 80 + tty->console.original_addr;
     if(tty->console.cursor >= tty->console.v_mem_limit)
            scroll_console(tty);
     flush_console(tty);
}
void Back_key(struct Tty *tty)
{
     if(tty->console.cursor > tty->console.original_addr)
     {
           tty->console.cursor --;
           tty->console.console_mem[tty->console.cursor * 2] = ' ';
           flush_console(tty);
     }
}

void key_encode(int32 key,struct Tty *tty)
{
       if(!(key & EXT)) 
            console_output(key,tty);
       else
       {
            switch(key)
            {
            case F1:
            case F2:
            case F3:
            case F4:
            case F5:
            case F6:
            case F7:
            case F8:
            case F9:
            case F10:
            case F11:
            case F12:
                 if (alt_l || alt_r) /* Alt + F1~F12 */	
				      ctl_tty(key);
			     break;
            case ENTER:
                 Enter_key(tty);
                 break;
            case BACKSPACE:
                 Back_key(tty);
                 break;
            default:
                 break;
            }
       }     
}

