#include "cpu/instr.h"
/*
Put the implementations of `call' instructions here.
*/



//E8 cw CALL rel16 7+m Call near, displacement relative to next instruction
make_instr_func(call_near)
{
    
    //print_asm_1("call_near", "", 1 + data_size / 8, &rel);
    
     //将esp/sp-2/4，
    cpu.esp=cpu.esp-data_size/8;
    
    //eip写入esp/sp的地址中  写的是call的下一条指令地址！否则会死循环不断执行call
    
    OPERAND m;
    
    operand_read(&opr_src);
    m.data_size = data_size;
    m.type = OPR_MEM;
    m.addr = cpu.esp;
    m.val = eip+1+data_size/8;
    operand_write(&m);
    
    
    //rel
    OPERAND rel;
    rel.type = OPR_IMM;
    rel.sreg = SREG_CS;
    rel.data_size = data_size;
    rel.addr = eip+1;
    operand_read(&rel);
    
    int offset = sign_ext(rel.val, data_size);
    cpu.eip += offset;
    //cpu.eip &= 0x0000FFFF;
    
    
    return 1+data_size/8;
}

