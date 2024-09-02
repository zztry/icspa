#include "cpu/instr.h"
/*
Put the implementations of `xor' instructions here.
*/
//宏make_instr_impl_2op(inst_name, src_type, dest_type, suffix)  

static void instr_execute_2op() 
{
	operand_read(&opr_src);
	
	operand_read(&opr_dest);
	opr_src.val = sign_ext(opr_src.val,opr_src.data_size);
	opr_dest.val = sign_ext(opr_dest.val,opr_dest.data_size);
	opr_dest.val = alu_xor(opr_src.val,opr_dest.val,data_size);
	operand_write(&opr_dest);
	
}

//   30 /r XOR r/m8,r8 2/6 Exclusive-OR byte register to r/m byte   b-8位  xor_r2rm_b
make_instr_impl_2op(xor,r,rm,b);

//31  xor_r2rm_v
make_instr_impl_2op(xor,r,rm,v);

//32
make_instr_impl_2op(xor,rm,r,b);

//33  xor_rm2r_v
make_instr_impl_2op(xor,rm,r,v);

//34  xor_i2a_b
make_instr_impl_2op(xor,i,a,b);

//35
make_instr_impl_2op(xor,i,a,v);

//80 /6  xor_i2rm_b
make_instr_impl_2op(xor,i,rm,b);

//81 /6
make_instr_impl_2op(xor,i,rm,v);

//83 /6 
make_instr_impl_2op(xor,i,rm,bv);
















