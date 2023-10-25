#include "cpu/instr.h"
/*
Put the implementations of `dec' instructions here.
*/
//dest-1
//宏make_instr_impl_1op(inst_name, src_type, suffix)
static void instr_execute_1op()
{
    //只有src，将src = src-1
    operand_read(&opr_src);
    uint32_t tmp =  cpu.eflags.CF;
    opr_src.val = alu_sub(1,opr_src.val,opr_src.data_size);//写反了……
    operand_write(&opr_src);
    cpu.eflags.CF = tmp;
    
}

//48+rw DEC r16 2 Decrement word register by 1
//48+rw DEC r32 2 Decrement dword register by 1  48-4f
//v-16/32 dec_r_v
make_instr_impl_1op(dec,r,v);