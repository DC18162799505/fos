/*------------------------------------------------------------------------------
   �ڴ���� 
------------------------------------------------------------------------------*/

#ifndef      _MEMORY_H_
#define      _MEMORY_H_

#define      Hd_mm           0x90000                       /*Ӳ����Ϣ�洢��λ*/
#define      Page_size       4096                          /*ҳ���С*/
#define      Kernel_mm       0x100000                      /*kernel.bin����ߵ�ַ*/
#define      Page_mm         0x200000                      /*���ҳĿ¼��ҳ�����Ϣ����ߵ�ַ*/
#define      Buff_mm         0x400000                      /*����������ߵ�ַ*/

#define      Add2mm32(value)      ((value) >> 2)           /*����ַת����int32���������*/
#define      Avl_mm_size(value)   ((value) - Buff_mm)      /*�����ڴ�Ĵ�С*/
#define      Add2pg8(value)       ((value) >> 12)          /*����ַת����ҳ������*/
#define      pg2add8(value)       ((value) << 12)          /*��ҳ������ת���ɵ�ַ*/

#define copy_page(from,to) \
__asm__("cld ; rep ; movsl"::"S" (from),"D" (to),"c" (1024))   /*����ҳ*/

#define      Un_avl          250                           /*��Ϊint8 a = 0; a -= 1;��a = 255,����Un_avl ����255*/
#define      Im_avl          0

#endif
/*�ڴ�ָ�� ��������ָ���ֵ��Ϊ0,��ʾ�ӵ�ַ0��ʼ*/
int8         *Phy_mm8;
int32        *Phy_mm32;
int32        Mm_size;

int8         Mm_map[Page_size * 2];

extern int init_mm();
extern int get_free_buff();
extern int get_free_app();

extern void free_page(unsigned long addr);                         /*�ͷ�һ������ҳ��*/
extern void free_page_tables(unsigned long base);                  /*�ͷ�һ��ҳ��*/
extern void copy_page_tables(unsigned long from,unsigned long to); /*����ҳ��*/
extern unsigned long put_page(unsigned cr3,unsigned long page,unsigned long address);
                                                                   /*�������ڴ�ӳ�䵽���Ե�ַ�ռ�*/
extern int share_page(unsigned long address);   
extern int try_to_share(unsigned long address,struct Task_struct *tem);                                                              
extern void do_page(unsigned long cr2,unsigned long error_no);
extern void do_wp_page(unsigned long cr2,unsigned long error_no);  /*ҳ�����쳣����*/
extern void do_no_page(unsigned long cr2,unsigned long error_no);  /*ȱҳ����*/
extern void un_wp_page(unsigned long * table_entry);               /*ҳ��������*/
extern void cr3_reload();                                          /*ˢ��cr3,��ΪTLB�����*/
