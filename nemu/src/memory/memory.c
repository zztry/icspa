#include "nemu.h"
#include "cpu/cpu.h"
#include "memory/memory.h"
#include "device/mm_io.h"
#include <memory.h>
#include <stdio.h>

uint8_t hw_mem[MEM_SIZE_B];

uint32_t hw_mem_read(paddr_t paddr, size_t len)
{
	uint32_t ret = 0;
	memcpy(&ret, hw_mem + paddr, len);
	return ret;
}

void hw_mem_write(paddr_t paddr, size_t len, uint32_t data)
{
	memcpy(hw_mem + paddr, &data, len);
}

uint32_t paddr_read(paddr_t paddr, size_t len)
{
	uint32_t ret = 0;
#ifdef CACHE_ENABLED
	ret = cache_read(paddr, len);     // 通过cache进行读
#else
	ret = hw_mem_read(paddr, len);
#endif
	return ret;
}

void paddr_write(paddr_t paddr, size_t len, uint32_t data)
{
#ifdef CACHE_ENABLED
	cache_write(paddr, len, data);    // 通过cache进行写
#else
	hw_mem_write(paddr, len, data);
#endif
}

uint32_t laddr_read(laddr_t laddr, size_t len)
{
    assert(len == 1 || len == 2 || len == 4);
#ifdef IA32_PAGE
    if( cpu.cr0.pg ) {
        //printf("cpu.cr0.pg=1 now.  laddr_read  \n");
        //fflush(stdout);
        //assert(0);
		if ((laddr>>12) !=((laddr+len-1)>>12)) {
		    uint32_t len1 = (((laddr>>12)+1)<<12)-laddr;
		    uint32_t addr1 = page_translate(laddr);  //低位
		    uint32_t addr2 = page_translate( ((laddr>>12)+1)<<12 );
		    uint32_t ret1 = paddr_read(addr1,len1);
		    uint32_t ret2 = paddr_read(addr2,len-len1);
		    return ret1+ (ret2<<(8*len1));
			/* this is a special case, you can handle it later. */			
		} 
		else {
			uint32_t hwaddr = page_translate(laddr);
			return paddr_read(hwaddr, len);	
		}
	}
	else {
	    return paddr_read(laddr, len);
	}
#else
	return paddr_read(laddr, len);
#endif
}

void laddr_write(laddr_t laddr, size_t len, uint32_t data)
{
#ifdef IA32_PAGE
    if(cpu.cr0.pg){
        //printf("cpu.cr0.pg=1 now.  laddr_write  \n");
        //fflush(stdout);
        if ((laddr>>12) !=((laddr+len-1)>>12)) {
            printf("cpu.cr0.pg=1 now.  laddr_write  \n");
            fflush(stdout);
		    uint32_t len1 = (((laddr>>12)+1)<<12)-laddr;
		    uint32_t len2 = len - len1;
		    uint32_t addr1 = page_translate(laddr);  //低位
		    uint32_t addr2 = page_translate( ((laddr>>12)+1)<<12 );
		    uint32_t data1 = data - ((data>>(8*len1))<<(8*len1));
		    uint32_t data2 = (data>>(8*len1));
		    paddr_write(addr1,len1,data1);
		    paddr_write(addr2,len2,data2);
		} 
		else {
			uint32_t hwaddr = page_translate(laddr);
		    paddr_write(hwaddr, len ,data);
		}
        
    }
    else{
        paddr_write(laddr, len, data);
    }
#else
	paddr_write(laddr, len, data);
#endif
}

uint32_t vaddr_read(vaddr_t vaddr, uint8_t sreg, size_t len)
{
	assert(len == 1 || len == 2 || len == 4);
#ifdef IA32_SEG
    if(cpu.cr0.pe){
	    uint32_t ld=segment_translate(vaddr,sreg);
	    return laddr_read(ld,len);
	}
	return laddr_read(vaddr, len);
#else
    return laddr_read(vaddr, len);
#endif
	
	
}

void vaddr_write(vaddr_t vaddr, uint8_t sreg, size_t len, uint32_t data)
{
	assert(len == 1 || len == 2 || len == 4);
#ifdef IA32_SEG
	if(cpu.cr0.pe) {
		uint32_t ld = segment_translate(vaddr, sreg);
		laddr_write(ld, len, data);
	}
	else{
	    laddr_write(vaddr, len, data);
	}
#else
	laddr_write(vaddr, len, data);
#endif
}

void init_mem()
{
	// clear the memory on initiation
	memset(hw_mem, 0, MEM_SIZE_B);
#ifdef CACHE_ENABLED
	init_cache();                             // 初始化cache
#endif

#ifdef TLB_ENABLED
	make_all_tlb();
	init_all_tlb();
#endif
}

uint32_t instr_fetch(vaddr_t vaddr, size_t len)
{
	assert(len == 1 || len == 2 || len == 4);
	return vaddr_read(vaddr, SREG_CS, len);
}

uint8_t *get_mem_addr()
{
	return hw_mem;
}
