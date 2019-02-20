/*------------------------------------------------------------------------------
   ¼Ä´æÆ÷¿ØÖÆ 
------------------------------------------------------------------------------*/

#ifndef      _REGCTL_H_
#define      _REGCTL_H_

#define ltr(n) __asm__("ltr %%ax"::"a" (n))
#define lldt(n) __asm__("lldt %%ax"::"a" (n))

#endif

void      Change_eflages();
void      Sgdt_call(Gdt_Ptr*);
void      Sidt_call(Idt_Ptr*);

inline unsigned char get_fs_byte(const char * addr);
inline unsigned short get_fs_word(const unsigned short *addr);
inline unsigned long get_fs_long(const unsigned long *addr);
inline void put_fs_byte(char val,char *addr);
inline void put_fs_word(short val,short * addr);
inline void put_fs_long(unsigned long val,unsigned long * addr);
inline unsigned long get_fs();
inline unsigned long get_ds();
inline void set_fs(unsigned long val);

inline unsigned long get_cr2_long();
inline unsigned long get_cr3_long();
inline unsigned long put_cr3_long(const unsigned long value);
