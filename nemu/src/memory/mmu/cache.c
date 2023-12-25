#include "memory/mmu/cache.h"
#include "memory/memory.h"
#include <stdio.h>
#include <stdlib.h>

//64 * 1024  共64KB
//8-way set associative
//共有 2^10行 ，2^7组 ,每组2^3=8行
//32-13 = 19 : 标记位      7: 组号   6: 块内地址
#ifdef CACHE_ENABLED
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
    
	uint32_t in_addr = paddr & 0x3f;   //块内地址
	uint32_t group = (paddr >> 6) & 0x7f;     //组号
	uint32_t tag_ = paddr >> 13;      //标记
	//如果跨行/块 先分割长度
	int len1 = len;
	int len2 = 0;
	if (64 - in_addr < len)
	{
		len1 = 64 - in_addr;
		len2 = len - len1;
	}
	for(int i=0;i<8;i++)
	{
		if(caches[group*8+i].tag==tag_&&caches[group*8+i].valid_bit==true)
		{
			if(len2==0)
			{
			    memcpy(caches[group*8+i].data+in_addr,&data,len);
			    caches[i].tag = tag_;
				caches[i].valid_bit = true;
			}
			else
			{
				cache_write(paddr,len1,data);
				cache_write(paddr+len1,len2,data>>(8*len1));
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
	uint32_t in_addr = paddr & 0x3f;   //块内地址
	uint32_t group = (paddr >> 6) & 0x7f;     //组号
	uint32_t tag_ = paddr >> 13;      //标记
	

    //如果跨行/块 先分割长度
	int len1 = len;
	int len2 = 0;
	if (64 - in_addr < len)
	{
		len1 = 64 - in_addr;
		len2 = len - len1;
	}
	
	bool is_match = false;//是否命中
	int pos = -1;//判断该组是否满,值为第一个无效的行
	for(int i=0;i<8;i++)
	{
	    if(caches[group*8+i].valid_bit==true)
	    {
	        
	        if(caches[group*8+i].tag==tag_)
	        {
	            is_match=true;
	            if (len2 == 0)//不跨行
			    {
				    memcpy(&ret, (void*)(&caches[group*8+i].data[in_addr]), len);
			    }
			    else//跨行
			    {
			        uint32_t ret1=0;
		    	    //读取前半部分
				    memcpy(&ret1, (void*)(&caches[group*8+i].data[in_addr]), len1);
				    //读取后半部分
				    uint32_t ret2 =0;
				    ret2=cache_read(paddr + len1, len2);//如果跨组/行都会在这里解决
				    //后半部分为高位，左移
				    ret2 = ret2 << (8 * len1);
				    ret = ret1 | ret2;
			    }
			    break;
	        }
	    }
	    else
	    {
	        if(pos==-1)
	        {
	            pos = i;
	        }
	    }
		
	}
	if(is_match == false)
	{
		memcpy(&ret,hw_mem+paddr,len);
		if(pos!=-1)
		{
		    caches[group*8+pos].valid_bit=true;
			caches[group*8+pos].tag=tag_;
			memcpy(caches[group*8+pos].data,hw_mem+paddr-in_addr,64);
		}
		else
		{
		    srand((unsigned)time(0));
			pos=rand()%8;
			caches[group*8+pos].valid_bit=true;
			caches[group*8+pos].tag=tag_;
			memcpy(caches[group*8+pos].data,hw_mem+paddr-in_addr,64);
		}
	}
	return ret;
}
#else
#endif


