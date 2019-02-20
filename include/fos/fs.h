#ifndef _FS_H_
#define _FS_H_

#define NR_FILES        64

#define READ            0
#define WRITE           1

#define FL_FAT1         01            /*fat1��Ŀ�ʼ����*/
#define FL_FAT2         10            /*fat2��Ŀ�ʼ����*/
#define FL_ROOT         19            /*��Ŀ¼��Ŀ�ʼ����*/
#define FL_DATA         33            /*�������Ŀ�ʼ����*/

#define DIR_NR_SEC      14            /*��Ŀ¼��ռ��������*/
#define FAT_NR_SEC      9             /*fat����ռ��������*/

/*fat12�ļ�ϵͳ�������ϵ���Ŀ��ʽ*/
struct Fat12
{
	  char name[8];
	  char name_ext[3];
	  char reserve[10];
	  int16 time;
	  int16 data;
	  int16 fstclus;                /*��ʼ�Ĵغ�*/
	  int32 size;    
};

struct Zone
{
	  unsigned long   page;         /*ҳ���ַ*/
	  int   lock;                   /*��*/
	  int   dirt;                   /*��λ*/
	  int   uptodata;               /*�Ƿ����ڴ���ڴ�һ��*/
	  int   sector;                 /*��ʼ������*/
	  struct Task_struct *waiting;  /*�ȴ����������Ķ���*/
};

/*ÿ���ļ���8��������,��ҳΪ��λ*/
struct File
{
	  int    fd;                    /*�ļ����*/
	  struct Fat12 fat;
	  struct Zone zones[8];         /*������*/ 
	  int  counts;                  /*���ô���*/ 
};

struct Super_block
{
	  int dirt;
	  int lock;
	  int read;
	  struct Task_struct *waiting;
	  unsigned char Root_dir[224 * 32];      /*��Ŀ¼������*/
	  unsigned char Fat_sec[9 * 512];        /*FATĿ¼������*/
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
