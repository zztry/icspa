#include "cpu/instr.h"
/*
Put the implementations of `iret' instructions here.
*/

make_instr_func(iret)
{
    OPERAND m;
    m.sreg = SREG_SS;
    m.type = OPR_MEM;

    m.data_size = 32;
    m.addr = cpu.esp;
    operand_read(&m);
    cpu.eip = m.val;
    cpu.esp+=4;
    
    m.data_size = 32;
    m.addr = cpu.esp;
    operand_read(&m);
    cpu.cs.val = m.val&0xFFFF;
    cpu.esp+=4;

    m.data_size = 32;
    m.addr = cpu.esp;
    operand_read(&m);
    cpu.eflags.val = m.val;
    cpu.esp+=4;

    return 0;

}
