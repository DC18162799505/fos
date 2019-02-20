#include "type.h"
#include "protect.h"
#include "sys\proc.h"
#include "sys\kernel.h"


int set_descriptor(DESCRIPTOR * p_desc, int32 base, int32 limit, int16 attribute)
{
	p_desc->limit_low		    = limit & 0x0FFFF;		// 段界限 1		(2 字节)
	p_desc->base_low		    = base & 0x0FFFF;		// 段基址 1		(2 字节)
	p_desc->base_mid		    = (base >> 16) & 0x0FF;		// 段基址 2		(1 字节)
	p_desc->attr1			    = attribute & 0xFF;		// 属性 1
	p_desc->limit_high_attr2	= ((limit >> 16) & 0x0F) | ((attribute >> 8) & 0xF0);
                                         // 段界限 2 + 属性 2
	p_desc->base_high		    = (base >> 24) & 0x0FF;		// 段基址 3		(1 字节)
	
    return 0;
}
int set_idt_desc(int32 vector, int32 desc_type, int_handler handler, int32 privilege)
{
	GATE *	p_gate	= &Idt[vector];
	int32	base	= (int32)handler;
	p_gate->offset_low	= base & 0xFFFF;
	p_gate->selector	= Selector_kernel_cs;
	p_gate->dcount		= 0;
	p_gate->attr		= desc_type | (privilege << 5);
	p_gate->offset_high	= (base >> 16) & 0xFFFF;
	
	return 0;
}
int32 seg2phys(int16 seg)
{
	DESCRIPTOR* p_dest = &Gdt[seg >> 3];

	return (p_dest->base_high << 24) | (p_dest->base_mid << 16) | (p_dest->base_low);
}
