#include "cpu/instr.h"
/*
Put the implementations of `test' instructions here.
*/

make_instr_func(test_r2rm_l)//32->32
{
    cpu.eflags.CF=0;
    cpu.eflags.OF=0;
    
    //OPERAND r,rm;//源，目的 操作数
    
    //rm.data_size = data_size; // data_size是个全局变量，表示操作数的比特长度
    //int len = 1;                          // opcode 长度1字节
    //len += modrm_rm(eip + 1, &rm); // 读ModR/M字节，rm的type和addr会被填写
    
    
    return 2;
}
