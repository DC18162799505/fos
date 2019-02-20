/*------------------------------------------------------------------------------
   时钟数据结构 
------------------------------------------------------------------------------*/

#ifndef     _TIME_H_
#define     _TIME_H_

#define     TIME_SYSTEM_SECOND       0x00
#define     TIME_ALARM_SECOND        0x01
#define     TIME_SYSTEM_MINUTE       0x02
#define     TIME_ALARM_MINUTE        0x03
#define     TIME_SYSTEM_HOUR         0x04
#define     TIME_ALARM_HOUR          0x05
#define     TIME_SYSTEM_WEEK         0x06         /*01 = SUNDAY , 02 TUESDAY , ect.*/
#define     TIME_SYSTEM_DATE         0x07         /*00 ~ 31*/
#define     TIME_SYSTEM_MONTH        0x08         /*01 ~ 12*/
#define     TIME_SYSTEM_YEAR         0x09         /*00 = 2000,01 = 2001,ect.*/

typedef struct Tm
{
        int sec;
        int min;
        int hour;
        int week;
        int data;
        int month;
        int year;
}Time_type;

#endif

Time_type   Time;
