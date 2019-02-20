#ifndef _ERRNO_H
#define _ERRNO_H

/* -----------------------------------------------------------------------------
  ����linux 0.11�������� 
                                              by  micklongen,2007.3.27 
----------------------------------------------------------------------------- */

extern int errno;

#define ERROR       99           /* һ����� */
#define EPERM        1           /* ����û����� */
#define ENOENT       2           /* �ļ���Ŀ¼������ */
#define ESRCH        3           /* ָ���Ľ��̲����� */
#define EINTR        4           /* �жϵ�ϵͳ���� */
#define EIO          5           /* ����/������� */
#define ENXIO        6           /* ָ���豸���ߵ�ַ������ */
#define E2BIG        7           /* �����б�̫�� */
#define ENOEXEC      8           /* ִ�г����ʽ���� */
#define EBADF        9           /* �ļ������������������ */
#define ECHILD      10           /* ���̲����� */
#define EAGAIN      11           /* ��Դ��ʱ���� */
#define ENOMEM      12           /* �ڴ治�� */
#define EACCES      13           /* û�����Ȩ�� */
#define EFAULT      14           /* ��ַ�� */
#define ENOTBLK     15           /* ���ǿ��豸�ļ� */
#define EBUSY       16           /* ��Դ��æ */
#define EEXIST      17           /* �ļ��Ѵ��� */
#define EXDEV       18           /* �Ƿ����� */
#define ENODEV      19           /* �豸������ */
#define ENOTDIR     20           /* ����Ŀ¼�ļ� */
#define EISDIR      21           /* ��Ŀ¼�ļ� */
#define EINVAL      22           /* ������Ч */
#define ENFILE      23           /* ϵͳ��̫���ļ� */
#define EMFILE      24           /* ���ļ���̫�� */
#define ENOTTY      25           /* ��ǡ����IO���Ʋ�����û��tty�նˣ� */
#define ETXTBSY     26           /* ����ʹ�� */
#define EFBIG       27           /* �ļ�̫�� */
#define ENOSPC      28           /* �豸�������豸�Ѿ�û�пռ䣩 */
#define ESPIPE      29           /* ��Ч���ļ�ָ���ض�λ */
#define EROFS       30           /* �ļ�ϵͳֻ�� */
#define EMLINK      31           /* ����̫�� */
#define EPIPE       32           /* �ܵ��� */
#define EDOM        33           /* ����� */
#define ERANGE      34           /* ���̫�� */
#define EDEADLK     35           /* ������Դ���� */
#define ENAMETOOLONG    36       /* �ļ���̫�� */
#define ENOLCK      37           /* û���������� */
#define ENOSYS      38           /* ���ܻ�û��ʵ�� */
#define ENOTEMPTY   39           /* Ŀ¼���� */

#endif
