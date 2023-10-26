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
    
    //OPERAND m;
    
    
    //m.data_size = data_size;
    //m.type = OPR_MEM;
    //m.addr = cpu.esp;
    //m.val = eip;
    //operand_read(&m);
    //cpu.ebp = m.val;
    
    
    cpu.esp += data_size/8;
    //eip = m.val;
    
    
    return 1;
}