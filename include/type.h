/*------------------------------------------------------------------------------
   类型定义 
------------------------------------------------------------------------------*/

#ifndef      _TYPE_H_
#define      _TYPE_H_

#define      NULL                0

typedef      char                int8;
typedef      unsigned short      int16;
typedef      unsigned long       int32;

typedef	     void	(*int_handler)	();
typedef	     void	(*irq_handler)	(int32 irq);
typedef      void   (*pf_handler)   ();
#endif
