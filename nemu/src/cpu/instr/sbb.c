#include "cpu/instr.h"
/*
Put the implementations of `sbb' instructions here.
*/
static void instr_execute_2op() 
{
	operand_read(&opr_src);
	
	operand_read(&opr_dest);
	opr_src.val = sign_ext(opr_src.val,opr_src.data_size);
	//opr_dest.val = sign_ext(opr_dest.val,opr_dest.data_size);
	opr_dest.val = alu_sbb(opr_src.val,opr_dest.val,data_size);
	operand_write(&opr_dest);
	
}


//1b  sbb_rm2r_v
make_instr_impl_2op(sbb,rm,r,v);

//18  sbb_r2rm_b
make_instr_impl_2op(sbb,r,rm,b);

//19
make_instr_impl_2op(sbb,r,rm,v);

//1a  sbb_rm2r_b
make_instr_impl_2op(sbb,rm,r,b);

//1c  sbb_i2a_b
make_instr_impl_2op(sbb,i,a,b);

//1d
make_instr_impl_2op(sbb,i,a,v);







