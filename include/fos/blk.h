/*------------------------------------------------------------------------------
  ���豸���� 
------------------------------------------------------------------------------*/

#ifndef        _BLK_H_
#define        _BLK_H_

#define        NR_REQUEST                32

struct Request 
{
    int cmd;                             /* READ or WRITE    */
    int errors;                          /* �����������     */
    int32 block;                         /* ��ʼ����         */
    int32 nr_sectors;                    /* ��/д������      */
    char *buffer;                        /* ���ݻ�����       */
    struct Task_struct * waiting;        /* ����ȴ�����ϵͳ��ɵĵط� */
    struct Zone *bh;
    struct Request * next;               /* ָ����һ�������� */
};

#endif

struct Request *current_request;         /* ���������ͷָ��*/
struct Request req_list[NR_REQUEST];

extern int get_req();
extern void add_request(struct Request * req);
extern inline void lock_buffer(struct Zone * bh);
extern inline void unlock_buffer(struct Zone * bh);
extern void operation_block(int rw, struct Zone * bh);
extern void make_request(int rw, struct Zone * bh);
extern void end_request(int uptodate);
extern void blk_dev_init(void);
