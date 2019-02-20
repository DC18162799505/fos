/*------------------------------------------------------------------------------
  ��ʾ�� 
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

struct Console                           /*Console �ĳ�Ա������wordΪ��λ*/
{
          int32       current_addr;
          int32       original_addr;
          int32       v_mem_limit;
          int32       cursor;            /*�������λ��*/
          int8        *console_mem;      /*����̨���*/
};

#endif

void set_cursor(int32 position);  /*���ù��λ��*/
void set_video(int32 addr);       /*������Ļλ��*/

