#include "cpu/instr.h"
/*
Put the implementations of `and' instructions here.
*/
//用宏实现make_instr_impl_2op(inst_name, src_type, dest_type, suffix)  

static void instr_execute_2op() 
{
	operand_read(&opr_src);
	operand_read(&opr_dest);
	opr_src.val = sign_ext(opr_src.val,opr_src.data_size);
	opr_dest.val = sign_ext(opr_dest.val,opr_dest.data_size);
	
	opr_dest.val = alu_and(opr_src.val,opr_dest.val,data_size);
	//cpu.eflags.CF = 0;
	//cpu.eflags.OF = 0;
	operand_write(&opr_dest);
	
}

//83 /4 ib AND r/m16,imm8 2/7 AND sign-extended immediate byte with r/m word
//83 /4 ib AND r/m32,imm8 2/7 AND sign-extended immediate byte with r/m dword
make_instr_impl_2op(and,i,rm,bv);

//22 and_rm2r_b
make_instr_impl_2op(and,rm,r,b);

//21  and_r2rm_v
make_instr_impl_2op(and,r,rm,v);

//81  /4 and_i2rm_v
make_instr_impl_2op(and,i,rm,v);

