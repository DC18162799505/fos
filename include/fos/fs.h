#ifndef _FS_H_
#define _FS_H_

#define NR_FILES        64

#define READ            0
#define WRITE           1

#define FL_FAT1         01            /*fat1表的开始扇区*/
#define FL_FAT2         10            /*fat2表的开始扇区*/
#define FL_ROOT         19            /*根目录表的开始扇区*/
#define FL_DATA         33            /*数据区的开始扇区*/

#define DIR_NR_SEC      14            /*根目录所占的扇区数*/
#define FAT_NR_SEC      9             /*fat表所占的扇区数*/

/*fat12文件系统在软盘上的条目格式*/
struct Fat12
{
	  char name[8];
	  char name_ext[3];
	  char reserve[10];
	  int16 time;
	  int16 data;
	  int16 fstclus;                /*开始的簇号*/
	  int32 size;    
};

struct Zone
{
	  unsigned long   page;         /*页面地址*/
	  int   lock;                   /*锁*/
	  int   dirt;                   /*脏位*/
	  int   uptodata;               /*是否与内存快内存一致*/
	  int   sector;                 /*开始扇区号*/
	  struct Task_struct *waiting;  /*等待该数据区的队列*/
};

/*每个文件由8个数据区,以页为单位*/
struct File
{
	  int    fd;                    /*文件句柄*/
	  struct Fat12 fat;
	  struct Zone zones[8];         /*数据区*/ 
	  int  counts;                  /*引用次数*/ 
};

struct Super_block
{
	  int dirt;
	  int lock;
	  int read;
	  struct Task_struct *waiting;
	  unsigned char Root_dir[224 * 32];      /*根目录缓冲区*/
	  unsigned char Fat_sec[9 * 512];        /*FAT目录缓冲区*/
};

#endif

struct File files[NR_FILES];
struct Super_block super_block;

extern void init_Zone(struct Zone* tmp);
extern void init_fs();
extern int request_fs();
extern int load_file(char *fname);
extern int cal_clus(int head);
extern void request_zone(int rw,unsigned long addr);
