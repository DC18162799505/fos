/*------------------------------------------------------------------------------
  硬盘 
------------------------------------------------------------------------------*/

#ifndef        _HD_H_
#define        _HD_H_

/*诊断命令的错误值*/
#define        Hd_no              0x01
#define        Hd_controller      0x02
#define        Hd_sector          0x03
#define        Hd_ecc             0x04
#define        Hd_cpu             0x05

/*其他命令的错误值*/
#define        Hd_data_flags_lost 0x01
#define        Hd_track0          0x02
#define        Hd_command_lost    0x04
#define        Hd_ID_lost         0x10
#define        Hd_ecc_error       0x40
#define        Hd_bad_sector      0x80

/*主状态寄存器命令*/
/*reading*/ 
#define        ERR_STAT           0x01              /*命令执行错误*/
#define        INDEX_STAT         0x02              /*收到索引*/ 
#define        ECC_STAT           0x04              /*ecc检验错误*/
#define        DRQ_STAT           0x08              /*数据请求服务*/
#define        SEEK_STAT          0x10              /*驱动器寻道结束*/ 
#define        WRERR_STAT         0x20              /*驱动器故障*/
#define        READY_STAT         0x40              /*驱动器准备好*/
#define        BUSY_STAT          0x80              /*控制器忙碌*/
/*writing*/
#define        WIN_RESTORE        0x10              /*驱动器重新校正*/
#define        WIN_READ           0x20              /*读扇区*/
#define        WIN_WRITE          0x30              /*写扇区*/
#define        WIN_VERIFY         0x40              /*扇区检验*/
#define        WIN_FORMAT         0x50              /*格式化磁道*/
#define        WIN_INIT           0x60              /*控制器初始化*/
#define        WIN_SEEK           0x70              /*寻道*/
#define        WIN_DIAGNOSE       0x90              /*控制器诊断*/
#define        WIN_SPECIFY        0x91              /*建立控制器参数*/

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
extern  int controller_ready();                     /*返回非0表示成功*/
extern  int win_result();                           /*检查硬盘执行命令后的状态，如果成功，返回0*/
extern  int drive_busy(void);                       /*等待硬盘就绪，成功返回0*/
extern  void init_hd();
