#include "cpu/instr.h"
/*
Put the implementations of `leave' instructions here.
*/

make_instr_func(leave)
{
    cpu.esp = cpu.ebp;
    
    //ebp pop
    
    OPERAND m;
    
    
    m.data_size = data_size;
    m.type = OPR_MEM;
    m.addr = cpu.ebp;
    //m.val = eip;
    operand_read(&m);
    cpu.ebp = m.val;
    
    cpu.esp += data_size/8;
    //eip = m.val;
    
    
    return 1;
}
