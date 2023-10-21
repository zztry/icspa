#include "cpu/instr.h"
/*
Put the implementations of `xor' instructions here.
*/
//宏make_instr_impl_2op(inst_name, src_type, dest_type, suffix)  

static void instr_execute_2op() 
{
	operand_read(&opr_src);
	
	operand_read(&opr_dest);
	
	opr_dest.val = alu_xor(opr_src.val,opr_dest.val,data_size);
	operand_write(&opr_dest);
	
}

//   30 /r XOR r/m8,r8 2/6 Exclusive-OR byte register to r/m byte   b-8位  xor_r2rm_b
make_instr_impl_2op(xor,r,rm,b);
