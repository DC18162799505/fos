#include "type.h"
#include "protect.h"

int Ptrctl(int32 *va,int32 *vb)
{   
       *va = (*va << 16) + (*vb >> 16);
       *vb = *vb & 0x0000ffff ;      
       return 0;
}
