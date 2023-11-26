#include "memory/mmu/cache.h"
#include "memory/memory.h"
#include <stdio.h>
#include <stdlib.h>

//64 * 1024  共64KB
//8-way set associative
//共有 2^10行 ，2^7组 ,每组2^3=8行
//32-13 = 19 : 标记位      7: 组号   6: 块内地址

CacheLine caches[1024];


// init the cache
void init_cache()
{
	// implement me in PA 3-1
	for(int i = 0;i<1024;i++)
	{
	    caches[i].valid_bit = false;
	    caches[i].tag = 0;
	    for(int j = 0;j<64;j++)
	    {
	        caches[i].data[j]=0;
	    }
	}
	
}

// write data to cache
void cache_write(paddr_t paddr, size_t len, uint32_t data)
{   
	
	
	
}

// read data from cache
uint32_t cache_read(paddr_t paddr, size_t len)
{
    
	// implement me in PA 3-1
	
	
	
	
	return 0;
}


	                



