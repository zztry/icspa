#include "cpu/instr.h"
/*
Put the implementations of `pop' instructions here.
*/

//58 + rw POP r16 4 Pop top of stack into word register
//58 + rd POP r32 4 Pop top of stack into dword register
 
make_instr_func(pop_r_v)
{
    //print_asm_1("leave", "", 1, &rel);
    opr_src.val = cpu.esp;
    
    //ebp pop
    
    OPERAND m;//读取esp处存的地址的数值
    
    m.data_size = data_size;
    m.type = OPR_MEM;
    m.addr = cpu.esp;
    operand_read(&m);
    //cpu.ebp = m.val;
    
    
    OPERAND r;//要存到的寄存器
    r.data_size = data_size;
    r.type = OPR_REG;
    r.addr = opcode & 0x7;
    r.val = m.val;
    
    operand_write(&r);
    
    cpu.esp += data_size/8;
    
    
    //eip = m.val;
    
    
    return 1;
}