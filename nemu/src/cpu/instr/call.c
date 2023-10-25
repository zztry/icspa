#include "cpu/instr.h"
/*
Put the implementations of `call' instructions here.
*/



//E8 cw CALL rel16 7+m Call near, displacement relative to next instruction
make_instr_func(call_near)
{
    int len = 1;
    
    //opcode_entry[54]
     //将esp/sp-2/4，
    OPERAND esp_;
    esp_.data_size = 32;
    esp_.type = OPR_REG;
    esp_.addr = 4;
    operand_read(&esp_);
    esp_.val = esp_.val - 2;
    operand_write(&esp_);
    
    //ip写入esp/sp的地址中
    
    OPERAND m;
    
    operand_read(&opr_src);
    m.data_size = data_size;
    m.type = OPR_MEM;
    m.addr = esp_.val;
    m.val = eip&0x0000FFFF;
    operand_write(&m);
    
    
    //rel
    OPERAND rel;
    rel.type = OPR_IMM;
    rel.data_size = data_size;
    rel.addr = eip+1;
    operand_read(&rel);
    
    int offset = (eip + rel.val)&0x0000FFFF;
    cpu.eip +=offset;
    
    
    return len+data_size/8;
}