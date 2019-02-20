/*------------------------------------------------------------------------------
  显示器 
------------------------------------------------------------------------------*/

#ifndef        _CONSOLE_H_
#define        _CONSOLE_H_

#define        Cursor_f                  0xa
#define        Cursor_a                  0xb
#define        Addr_start_h              0xc
#define        Addr_start_l              0xd
#define        Cursor_h                  0xe
#define        Cursor_l                  0xf

#define        Video_mm                  0xB8000
#define        V_mem                     4000
#define        Original_addr             0x1000

struct Console                           /*Console 的成员都是以word为单位*/
{
          int32       current_addr;
          int32       original_addr;
          int32       v_mem_limit;
          int32       cursor;            /*光标所在位置*/
          int8        *console_mem;      /*控制台输出*/
};

#endif

void set_cursor(int32 position);  /*设置光标位置*/
void set_video(int32 addr);       /*设置屏幕位置*/

