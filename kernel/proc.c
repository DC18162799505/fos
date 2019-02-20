#include       "type.h"
#include       "protect.h"
#include       "string.h"
#include       "sys\proc.h"

void     wait(int *sig)
{
         while(*sig <= 0);
         *sig = *sig - 1;
}

void     signal(int *sig)
{
         *sig = *sig + 1;
}
