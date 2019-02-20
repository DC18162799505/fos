/*------------------------------------------------------------------------------
  信号常量 
------------------------------------------------------------------------------*/

#ifndef _SIGNAL_H_
#define _SIGNAL_H_

#define SIGHUP       1               /*挂断控制终端或进程*/
#define SIGINT       2               /*来自键盘的中断*/
#define SIGQUIT      3               /*来自键盘的退出*/
#define SIGILL       4               /*非法指令*/
#define SIGTRAP      5               /*跟踪断点*/
#define SIGABRT      6               /*异常结束*/
#define SIGIOT       6               /*同上*/
#define SIGUNUSED    7               /*没有使用*/
#define SIGFPE       8               /*协处理器出错*/
#define SIGKILL      9               /*强迫进程终止*/
#define SIGUSR1     10               /*用户信号1，进程可使用*/
#define SIGSEGV     11               /*无效内存引用*/
#define SIGUSR2     12               /*用户信号2，进程可使用*/
#define SIGPIPE     13               /*管道写出错，无读者*/ 
#define SIGALRM     14               /*实时定时器报警*/
#define SIGTERM     15               /*进程终止*/
#define SIGSTKFLT   16               /*栈出错（协处理器）*/
#define SIGCHLD     17               /*子进程停止或被终止*/
#define SIGCONT     18               /*恢复进程继续执行*/
#define SIGSTOP     19               /*停止进程的执行*/
#define SIGTSTP     20               /*tty发出停止进程，可忽视*/
#define SIGTTIN     21               /*后台进程请求输入*/
#define SIGTTOU     22               /*后台进程请求输出*/

#endif
