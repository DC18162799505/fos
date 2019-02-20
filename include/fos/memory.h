/*------------------------------------------------------------------------------
   内存管理 
------------------------------------------------------------------------------*/

#ifndef      _MEMORY_H_
#define      _MEMORY_H_

#define      Hd_mm           0x90000                       /*硬件信息存储单位*/
#define      Page_size       4096                          /*页面大小*/
#define      Kernel_mm       0x100000                      /*kernel.bin的最高地址*/
#define      Page_mm         0x200000                      /*存放页目录和页表的信息的最高地址*/
#define      Buff_mm         0x400000                      /*缓冲区的最高地址*/

#define      Add2mm32(value)      ((value) >> 2)           /*将地址转换成int32数组的索引*/
#define      Avl_mm_size(value)   ((value) - Buff_mm)      /*可用内存的大小*/
#define      Add2pg8(value)       ((value) >> 12)          /*将地址转换成页面索引*/
#define      pg2add8(value)       ((value) << 12)          /*将页面索引转换成地址*/

#define copy_page(from,to) \
__asm__("cld ; rep ; movsl"::"S" (from),"D" (to),"c" (1024))   /*复制页*/

#define      Un_avl          250                           /*因为int8 a = 0; a -= 1;则a = 255,所以Un_avl 不用255*/
#define      Im_avl          0

#endif
/*内存指针 ：将两个指针的值赋为0,表示从地址0开始*/
int8         *Phy_mm8;
int32        *Phy_mm32;
int32        Mm_size;

int8         Mm_map[Page_size * 2];

extern int init_mm();
extern int get_free_buff();
extern int get_free_app();

extern void free_page(unsigned long addr);                         /*释放一个物理页面*/
extern void free_page_tables(unsigned long base);                  /*释放一个页表*/
extern void copy_page_tables(unsigned long from,unsigned long to); /*复制页表*/
extern unsigned long put_page(unsigned cr3,unsigned long page,unsigned long address);
                                                                   /*将物理内存映射到线性地址空间*/
extern int share_page(unsigned long address);   
extern int try_to_share(unsigned long address,struct Task_struct *tem);                                                              
extern void do_page(unsigned long cr2,unsigned long error_no);
extern void do_wp_page(unsigned long cr2,unsigned long error_no);  /*页保护异常处理*/
extern void do_no_page(unsigned long cr2,unsigned long error_no);  /*缺页处理*/
extern void un_wp_page(unsigned long * table_entry);               /*页保护处理*/
extern void cr3_reload();                                          /*刷新cr3,是为TLB服务的*/
