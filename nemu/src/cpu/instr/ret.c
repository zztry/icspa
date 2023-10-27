#include "cpu/instr.h"
/*
Put the implementations of `ret' instructions here.
*/
make_instr_func(ret_near)//c3
{
    //cpu.esp = cpu.ebp;
    
    //ebp pop
    
    OPERAND m;
    
    m.data_size = data_size;
    m.type = OPR_MEM;
    m.addr = cpu.esp;
    //m.val = eip;
    operand_read(&m);
    cpu.eip = m.val;
    //eip指向返回位置
    //jmp是用偏移量计算eip值的，所以把return的长度加上，这里直接给eip赋值，所以要考虑自身长度
    
    //出栈，
    cpu.esp += data_size/8;
    //eip = m.val;
    
    
    return 0;
}

//c2
make_instr_func(ret_near_imm16)
{
    
    operand_read(&opr_src);
    cpu.eip = opr_src.val;
    cpu.esp+=data_size/8;
    return 0;
}



