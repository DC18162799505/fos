/*------------------------------------------------------------------------------
  Ӳ�� 
------------------------------------------------------------------------------*/

#ifndef        _HD_H_
#define        _HD_H_

/*�������Ĵ���ֵ*/
#define        Hd_no              0x01
#define        Hd_controller      0x02
#define        Hd_sector          0x03
#define        Hd_ecc             0x04
#define        Hd_cpu             0x05

/*��������Ĵ���ֵ*/
#define        Hd_data_flags_lost 0x01
#define        Hd_track0          0x02
#define        Hd_command_lost    0x04
#define        Hd_ID_lost         0x10
#define        Hd_ecc_error       0x40
#define        Hd_bad_sector      0x80

/*��״̬�Ĵ�������*/
/*reading*/ 
#define        ERR_STAT           0x01              /*����ִ�д���*/
#define        INDEX_STAT         0x02              /*�յ�����*/ 
#define        ECC_STAT           0x04              /*ecc�������*/
#define        DRQ_STAT           0x08              /*�����������*/
#define        SEEK_STAT          0x10              /*������Ѱ������*/ 
#define        WRERR_STAT         0x20              /*����������*/
#define        READY_STAT         0x40              /*������׼����*/
#define        BUSY_STAT          0x80              /*������æµ*/
/*writing*/
#define        WIN_RESTORE        0x10              /*����������У��*/
#define        WIN_READ           0x20              /*������*/
#define        WIN_WRITE          0x30              /*д����*/
#define        WIN_VERIFY         0x40              /*��������*/
#define        WIN_FORMAT         0x50              /*��ʽ���ŵ�*/
#define        WIN_INIT           0x60              /*��������ʼ��*/
#define        WIN_SEEK           0x70              /*Ѱ��*/
#define        WIN_DIAGNOSE       0x90              /*���������*/
#define        WIN_SPECIFY        0x91              /*��������������*/

#define        Hd_drive_mask      0xA0

struct hd_node_struct
{
    int32 head;
    int32 sect;
    int32 cyl;
    int32 wpcom;
    int32 lzone;
    int32 ctl;
};

#endif

void (*hd_handler)(int32 irq);
extern  int controller_ready();                     /*���ط�0��ʾ�ɹ�*/
extern  int win_result();                           /*���Ӳ��ִ��������״̬������ɹ�������0*/
extern  int drive_busy(void);                       /*�ȴ�Ӳ�̾������ɹ�����0*/
extern  void init_hd();
