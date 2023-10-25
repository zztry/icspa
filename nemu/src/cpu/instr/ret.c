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
    
    cpu.esp -= data_size/8;
    //eip = m.val;
    
    
    return 1;
}
