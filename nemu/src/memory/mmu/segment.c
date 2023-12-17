#include "cpu/cpu.h"
#include "memory/memory.h"

// return the linear address from the virtual address and segment selector
uint32_t segment_translate(uint32_t offset, uint8_t sreg)
{
	/* TODO: perform segment translation from virtual address to linear address
	 * by reading the invisible part of the segment register 'sreg'
	 */
	
	return cpu.segReg[sreg].base+offset;
}

// load the invisible part of a segment register
void load_sreg(uint8_t sreg)
{
	/* TODO: load the invisibile part of the segment register 'sreg' by reading the GDT.
	 * The visible part of 'sreg' should be assigned by mov or ljmp already.
	 */
	 
	 //对应段表地址,64位8字节
	 
	 uint32_t segt_addr = (uint32_t)hw_mem + cpu.gdtr.base + cpu.segReg[sreg].index * 8;
	 SegDesc* sgdt = (SegDesc *)segt_addr;
	 
	 //laddr_read  laddr_read(laddr_t laddr, size_t len)
	 assert(sreg==0);
	 cpu.segReg[sreg].base = sgdt->base_15_0 + (sgdt->base_23_16<<16)+(sgdt->base_31_24<<24);
	 cpu.segReg[sreg].limit = sgdt->limit_15_0+(sgdt->limit_19_16<<16);
	 cpu.segReg[sreg].privilege_level = sgdt->privilege_level;
	 assert(cpu.segReg[sreg].base==0);
	 assert(cpu.segReg[sreg].limit == 0xfffff);
	 assert(sgdt->present==1);
	 assert(sgdt->granularity==1);
	 
	 
    
}
