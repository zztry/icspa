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
	}
	
}

// write data to cache
void cache_write(paddr_t paddr, size_t len, uint32_t data)
{   
    memcpy((void *)(hw_mem+paddr), &data, len);
    
	// implement me in PA 3-1
	uint32_t tag_ = paddr>>13;      //标记
	
	
	for(int i = 0;i<=1024;i++)
	{
	    if(caches[i].valid_bit==true&&caches[i].tag==tag_)//命中
	    {
	        caches[i].valid_bit = false;
	        break;
	    }
	   
	}
	
	
	
}

// read data from cache
uint32_t cache_read(paddr_t paddr, size_t len)
{
    
	// implement me in PA 3-1
	
	uint32_t ingr_addr = paddr & 0x3f;   //块内地址
	uint32_t group = (paddr>>6)&0x7f;     //组号
	uint32_t tag_ = paddr>>13;      //标记
	
	//组号对应从x1到x2行
	uint32_t begin_line = group*8;
	//uint32_t end_line = begin_line+7;
	
	//如果跨行/块 先分割长度
	int len1 = len;
	int len2 = 0;
	if(64-ingr_addr<len)
	{
	    len1 = 64-ingr_addr;
	    len2 = len-len1;
	}
	
	
	uint32_t ret;
	
	bool is_match = false;//是否命中
	uint32_t pos = 0;//判断该组是否满,值为第一个无效的行
	
	
	for(uint32_t i = begin_line;i<begin_line+8;i++)
	{
	    if(caches[i].valid_bit==true)
	    {
	        if(caches[i].tag==tag_)//命中，直接读取
	        {
	            is_match = true;
	            if(len2==0)//不跨行
	            {   
	                
	                memcpy(&ret,(void *)(&caches[i].data+ingr_addr),len);
	                
	            }
	            else//跨行
	            {
	                memcpy(&ret,(void *)(hw_mem+paddr),len);
	                
	            }
	            return ret;
	        }
	    }
	}
	
	
	//如果没有命中
	if(is_match==false)
	{
	    memcpy(&ret,(void *)(hw_mem+paddr),len);
	    
	    pos = begin_line;
	    memcpy((void *)caches[pos].data, (void *)(hw_mem+paddr-ingr_addr), 64); 
	    caches[pos].valid_bit = true;
		caches[pos].tag = tag_;
		
		
	    
	}
	
	
	
	return ret;
}


	                



