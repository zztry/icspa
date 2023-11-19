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
	// implement me in PA 3-1
	uint32_t ingr_addr = paddr & 0x3f;        //块内地址
	uint32_t group = (paddr& 0x1fff)>>6;      //组号
	uint32_t tag_ = (paddr>>13)&0x7ffff;      //标记
	
	//组号对应从x1到x2行
	uint32_t begin_line = group*8;
	uint32_t end_line = begin_line+7;
	
	//如果跨行/块 先分割长度
	int len1 = len;
	int len2 = 0;
	if(64-ingr_addr<len)
	{
	    len1 = 64-ingr_addr;
	    len2 = len-len1;
	}
	
	bool is_match = false;//是否命中
	for(int i = begin_line;i<=end_line;i++)
	{
	    if(caches[i].valid_bit==true)
	    {
	        
	        if(caches[i].tag==tag_)//命中
	        {
	            is_match = true;
	            if(len2==0)//不跨行
	            {
	                memcpy((void *)(hw_mem+paddr), &data, len);
	                memcpy(caches[i].data+ingr_addr, &data, len);
				    caches[i].tag = tag_;
				    caches[i].valid_bit = true;
	            }
	            else//跨行
	            {
	                memcpy((void *)(hw_mem+paddr), &data, len);
				    memcpy(caches[i].data+ingr_addr, &data, len1);
				    caches[i].tag = tag_;
				    caches[i].valid_bit = true;
				    cache_write(paddr+len1, len2, data>>(len1 * 8));
	            }
	        }
	    }
	   
	}
	
	if(is_match == false)
	{
	    memcpy((void *)(hw_mem+paddr), &data, len);
	}
	
	
	
	
}

// read data from cache
uint32_t cache_read(paddr_t paddr, size_t len)
{
	// implement me in PA 3-1
	
	uint32_t ingr_addr = paddr & 0x3f;   //块内地址
	uint32_t group = (paddr& 0x1fff)>>6;     //组号
	uint32_t tag_ = paddr>>13;      //标记
	
	//组号对应从x1到x2行
	uint32_t begin_line = group*8;
	uint32_t end_line = begin_line+7;
	
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
	uint32_t pos = -1;//判断该组是否满,值为第一个无效的行
	
	for(int i = begin_line;i<=end_line;i++)
	{
	    if(caches[i].valid_bit==true)
	    {
	        
	        if(caches[i].tag==tag_)//命中，直接读取
	        {
	            is_match = true;
	            if(len2==0)//不跨行
	            {   
	                //从后向前每次读取一个字节(从高位至低位)
	                /*for(int j = ingr_addr+len-1; j>=ingr_addr;j--)
	                {
	                    ret+=caches[i].data[j];
	                    if(j!=ingr_addr)
	                    {
	                        ret=ret<<8;
	                    }
	                    
	                }*/
	                memcpy(&ret,caches[i].data+ingr_addr,len);
	            }
	            else//跨行
	            {
	                //读取前半部分
	                for(int j = ingr_addr+len1-1;j>=ingr_addr;j--)
	                {
	                    ret+=caches[i].data[j];
	                    if(j!=ingr_addr)
	                    {
	                        ret=ret<<8;
	                    }
	                }
	                //memcpy(&ret,caches[i].data+ingr_addr,len1);
	                //读取后半部分
	                uint32_t ret2 = cache_read(paddr+len1,len2);//如果跨组/行都会在这里解决
	                //后半部分为高位，左移
	                ret2= ret2<<(8*len2);
	                ret = ret | ret2;
	                
	            }
	            break;
	        }
	    }
	    else//将pos调整为第一个无效行
	    {
	        if(pos==-1)
	        {
	            pos = i;
	        }
	    }
	}
	
	
	//如果没有命中
	if(is_match==false)
	{
	    memcpy(&ret,(void *)(hw_mem+paddr),len);
	    //查看是否有空行
	    if(pos!=-1)
	    {
	        //在第一个空行中写入
	        memcpy(caches[pos].data, (void *)(hw_mem+paddr-ingr_addr), 64);
	        caches[pos].valid_bit = true;
			caches[pos].tag = tag_;
	    }
	    else
	    {
	        //随机选取
	        pos = begin_line + (rand()%8);
	        memcpy(caches[pos].data, (void *)(hw_mem+paddr-ingr_addr), 64);
	        caches[pos].valid_bit = true;
			caches[pos].tag = tag_;
	    }
	    
	    
	    
	}
	
	
	
	return ret;
}

