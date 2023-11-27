#include "memory/mmu/cache.h"
#include "memory/memory.h"
#include <stdio.h>
#include <stdlib.h>

//64 * 1024  共64KB
//8-way set associative
//共有 2^10行 ，2^7组 ,每组2^3=8行
//32-13 = 19 : 标记位      7: 组号   6: 块内地址

CacheLine caches[1024];
extern uint8_t hw_mem[];

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
	memcpy((void *)(hw_mem+paddr), &data, len);
    
	uint32_t sign =(paddr>>13)&0x7ffff;
	uint32_t group_num =(paddr>>6)&0x7f;
	uint32_t offset=paddr&0x3f;
	int i;
	for(i=0;i<8;i++)
	{
		if(caches[group_num*8+i].tag==sign&&caches[group_num*8+i].valid_bit==true)
		{
			if(offset+len<=64)
				memcpy(caches[group_num*8+i].data+offset,&data,len);
			else
			{
				cache_write(paddr,64-offset,data);
				cache_write(paddr+64-offset,len+offset-64,data>>(8*(64-offset)));
			}
			break;
		}
	}
	
	
}

// read data from cache
uint32_t cache_read(paddr_t paddr, size_t len)
{
    
	// implement me in PA 3-1
	
	
	uint32_t ret;
	uint32_t sign =(paddr>>13)&0x7ffff;
	uint32_t group_num =(paddr>>6)&0x7f;
	uint32_t offset=paddr&0x3f;
	int i;
	for(i=0;i<8;i++)
	{
		if(caches[group_num*8+i].tag==sign&&cache[group_num*8+i].valid_bit==true)
		{	
			if(offset+len<=64)
				memcpy(&ret,caches[group_num*8+i].data+offset,len);
			else
			{
				uint32_t temp1=0,temp2=0;
				memcpy(&temp1,cache[group_num*8+i].data+offset,64-offset);
				temp2=cache_read(paddr+64-offset,offset+len-64)<<(8*(64-offset));
				ret=temp2|temp1;
			}
			break;
		}
	}
	if(i==8)
	{
		memcpy(&ret,hw_mem+paddr,len);
		for(i=0;i<8;i++)
		{
			if(caches[group_num*8+i].valid==0)
			{
				caches[group_num*8+i].valid=true;
				caches[group_num*8+i].tag=sign;
				memcpy(caches[group_num*8+i].data,hw_mem+paddr-offset,64);
				break;
			}
		}
		if(i==8)
		{
			srand((unsigned)time(0));
			i=rand()%8;
			caches[group_num*8+i].valid_bit=true;
			caches[group_num*8+i].tag=sign;
			memcpy(caches[group_num*8+i].data,hw_mem+paddr-offset,64);
		}
	}
	return ret;
}


	                



