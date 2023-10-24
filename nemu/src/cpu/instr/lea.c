#include "cpu/instr.h"
/*
Put the implementations of `lea' instructions here.
*/


make_instr_func(lea_rm2r_v)//m地址 源操作数rm 目的操作数r
{
    OPERAND rm, r;
    
    int len = 1;
    r.data_size = data_size;
    rm.data_size = data_size;
    len += modrm_r_rm(eip + 1, &r, &rm);
    //operand_read(&r);
    //operand_read(&opr_dest);
    //opr_src.val = signed_ext(opr_src.val,opr_src.data_size);
    r.val = rm.addr;
    /*
    if(opr_dest.data_size==16)
    {
        opr_dest.val = (0xffffffff>>16)&opr_src.addr;
    }
    else if(opr_dest.data_size==32)
    {
        opr_dest.val = opr_src.addr;//这里没处理16->32的0扩展
    }*/
    operand_write(&r);
    return len;
}
//8D /r LEA r16,m 2 Store effective address for m in register r16
//8D /r LEA r32,m 2 Store effective address for m in register r32
//8D /r LEA r16,m 2 Store effective address for m in register r16
//8D /r LEA r32,m 2 Store effective address for m in register r32