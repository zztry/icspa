#include "cpu/instr.h"
/*
Put the implementations of `leave' instructions here.
*/

make_instr_func(leave)
{
    //print_asm_1("leave", "", 1, &rel);
    cpu.esp = cpu.ebp;
    
    //ebp pop
    
    OPERAND m;
    
    
    m.data_size = data_size;
    m.type = OPR_MEM;
    m.addr = cpu.esp;
    m.sreg = SREG_DS;
    //m.val = eip;
    operand_read(&m);
    cpu.ebp = m.val;
    
    
    cpu.esp += data_size/8;
    //eip = m.val;
    
    
    return 1;
}
