#include "cpu/instr.h"
/*
Put the implementations of `or' instructions here.
*/

//用宏实现make_instr_impl_2op(inst_name, src_type, dest_type, suffix)  

static void instr_execute_2op() 
{
	operand_read(&opr_src);
	operand_read(&opr_dest);
	opr_src.val = sign_ext(opr_src.val,opr_src.data_size);
	opr_dest.val = sign_ext(opr_dest.val,opr_dest.data_size);
	
	opr_dest.val = alu_or(opr_src.val,opr_dest.val,data_size);
	//cpu.eflags.CF = 0;
	//cpu.eflags.OF = 0;
	operand_write(&opr_dest);
	
}
//0a   or_rm2r_b
make_instr_impl_2op(or,rm,r,b);

//0b
make_instr_impl_2op(or,rm,r,v);

//08
make_instr_impl_2op(or,r,rm,b);

//09  or_r2rm_v
make_instr_impl_2op(or,r,rm,v);


