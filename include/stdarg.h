/* -----------------------------------------------------------------------------
  参照标准c，有做一些修改
                                                by  micklongen,2007.3.27
----------------------------------------------------------------------------- */
#ifndef _STDARG_H
#define _STDARG_H

typedef char *va_list;

/* Amount of space required in an argument list for an arg of type TYPE.
   TYPE may alternatively be an expression whose type is used.  */
/*  参数是以双字为单位压栈的 */
#define __va_rounded_size(TYPE)  \
   (((sizeof (TYPE) + sizeof (int) - 1) / sizeof (int)) * sizeof (int))
 
/* AP指向可变参数 */
#define va_start(AP, LASTARG)                       \
  (AP = ((char *) &(LASTARG) + __va_rounded_size (LASTARG)))

void va_end (va_list AP)
{
     AP = 0; 
}
#define va_end(AP)

#define va_arg(AP, TYPE)                        \
 (AP += __va_rounded_size (TYPE),                   \
  *((TYPE *) (AP - __va_rounded_size (TYPE))))

#endif /* _STDARG_H */
