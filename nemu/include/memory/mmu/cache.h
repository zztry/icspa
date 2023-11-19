#ifndef __CACHE_H__
#define __CACHE_H__

#include "nemu.h"

#ifdef CACHE_ENABLED

//64 * 1024  共64KB
//8-way set associative
//共有 2^10行 ，2^7组 ,每组2^3=8行
//32-13 = 19 : 标记位      7: 组号   6: 块内地址
typedef struct CacheLine{
    bool valid_bit;     //有效位 1位
    uint32_t tag;        //标记  2^19
    uint8_t data[64]; //数据区 64B  2^6
};


// init the cache
void init_cache();

// write data to cache
void cache_write(paddr_t paddr, size_t len, uint32_t data);

// read data from cache
uint32_t cache_read(paddr_t paddr, size_t len);

#endif

#endif
