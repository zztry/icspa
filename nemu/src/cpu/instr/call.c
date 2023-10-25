#include "cpu/instr.h"
/*
Put the implementations of `call' instructions here.
*/



//E8 cw CALL rel16 7+m Call near, displacement relative to next instruction
make_instr_func(call_near)
{
    
    /*
    //opcode_entry[54]
     //将esp/sp-2/4，
    OPERAND esp_;
    esp_.data_size = 32;
    esp_.type = OPR_REG;
    esp_.addr = 4;
    operand_read(&esp_);
    esp_.val = esp_.val - data_size/8;
    operand_write(&esp_);
    
    //ip写入esp/sp的地址中
    
    OPERAND m;
    
    operand_read(&opr_src);
    m.data_size = 32;
    m.type = OPR_MEM;
    m.addr = esp_.val;
    m.val = eip;
    operand_write(&m);*/
    
    
    //rel
    OPERAND rel;
    rel.type = OPR_IMM;
    rel.data_size = data_size;
    rel.addr = eip+1;
    operand_read(&rel);
    
    int offset = sign_ext(rel.val, data_size);
    cpu.eip += offset;
    cpu.eip &= 0x0000FFFF;
    
    
    return 1+data_size/8;
}

