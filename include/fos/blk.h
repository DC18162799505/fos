/*------------------------------------------------------------------------------
  块设备处理 
------------------------------------------------------------------------------*/

#ifndef        _BLK_H_
#define        _BLK_H_

#define        NR_REQUEST                32

struct Request 
{
    int cmd;                             /* READ or WRITE    */
    int errors;                          /* 操作错误次数     */
    int32 block;                         /* 起始扇区         */
    int32 nr_sectors;                    /* 读/写扇区数      */
    char *buffer;                        /* 数据缓冲区       */
    struct Task_struct * waiting;        /* 任务等待操作系统完成的地方 */
    struct Zone *bh;
    struct Request * next;               /* 指向下一个请求项 */
};

#endif

struct Request *current_request;         /* 请求项队列头指针*/
struct Request req_list[NR_REQUEST];

extern int get_req();
extern void add_request(struct Request * req);
extern inline void lock_buffer(struct Zone * bh);
extern inline void unlock_buffer(struct Zone * bh);
extern void operation_block(int rw, struct Zone * bh);
extern void make_request(int rw, struct Zone * bh);
extern void end_request(int uptodate);
extern void blk_dev_init(void);
