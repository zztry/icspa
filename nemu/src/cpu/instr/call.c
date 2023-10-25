#include "cpu/instr.h"
/*
Put the implementations of `call' instructions here.
*/



//E8 cw CALL rel16 7+m Call near, displacement relative to next instruction
make_instr_func(call_near)
{
    int len = 1;
    
    //opcode_entry[54]
    
    //push(eip/ip)
    //将esp/sp-2，
    cpu.esp.val-=2;
    
    //eip写入sp的地址中
    OPERAND m;//m为esp地址
    m.data_size = data_size;
    m.type = OPR_MEM;
    m.addr = esp.val;
    m.val = (0x0000ffff&eip);
    operand_write(&m);
    
    OPERAND rel;
    rel.type = OPR_IMM;
    rel.data_size = data_size;
    rel.addr = eip+1;
    operand_read(&rel);
    
    cpu.eip.val = (cpu.eip.val + rel.val)&0x0000ffff;
    
    
    
    return len+data_size/8;
}