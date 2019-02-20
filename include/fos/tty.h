/*------------------------------------------------------------------------------
  终端控制台 
------------------------------------------------------------------------------*/
#ifndef        _TTY_H_
#define        _TTY_H_

#define        NR_BYTES          0x20
#define        NR_TTY            0x8

struct    Tty
{
          int32         buffer[NR_BYTES];
          int32         begin;
          int32         end;
          int32         count;
          int32         sn;                      /*当前是哪一个屏幕*/
          int32         lock;
          struct Console console;
};

#endif

struct  Tty      tty_table[NR_TTY];
struct  Tty      *current_tty;

/*屏幕控制*/
extern  void flush_console(struct Tty *tty);
extern  void console_output(int32 ch,struct Tty *tty);
extern  void scroll_console(struct Tty *tty);

/*键盘解码*/
void key_encode(int32 key,struct Tty *tty);
void Enter_key(struct Tty *tty);
void Back_key(struct Tty *tty);

extern  int    init_tty();
extern  void   key_receive(int32);
extern  void   ctl_tty(int32);

extern  void   write_tty(struct Tty* p_tty,char *buf,int len);
