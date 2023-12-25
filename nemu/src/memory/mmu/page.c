#include "cpu/cpu.h"
#include "memory/memory.h"

// translate from linear address to physical address
paddr_t page_translate(laddr_t laddr)
{
    //printf("\nPlease implement page_translate()\n");
	//fflush(stdout);
	//assert(0);
#ifndef TLB_ENABLED
	uint32_t addr1 = hw_mem + (cpu.cr3.pdbr<<12) +  (laddr>>22)*4 ;
	PDE* p1 = (void*)addr1;
	assert(p1->present==1);
	uint32_t addr2 = hw_mem + ((laddr>>12)&0x3ff)*4 + (p1->page_frame<<12);
	PTE* p2 = (void*)addr2;
	assert(p2->present==1);
	return (p2->page_frame<<12)+(laddr&0xfff);
	
#else
	return tlb_read(laddr) | (laddr & PAGE_MASK);
#endif
}
