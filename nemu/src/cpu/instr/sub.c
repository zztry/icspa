#include "cpu/instr.h"
/*
Put the implementations of `sub' instructions here.
*/
//用宏实现make_instr_impl_2op(inst_name, src_type, dest_type, suffix)  

static void instr_execute_2op() 
{
	operand_read(&opr_src);
	operand_read(&opr_dest);
	
	if(opr_src.data_size==8 && (opr_dest.data_size>=16))
	{
	    opr_dest.val=alu_sub(opr_dest.val,sign_ext(opr_src.val,opr_src.data_size),data_size);
	}
	else
	{
	    opr_dest.val=alu_sub(opr_dest.val,opr_src.val,data_size);
	}
	operand_write(&opr_dest);
	
}

//83 /5 ib SUB r/m16,imm8 2/7 Subtract sign-extended immediate byte from r/m word
//83 /5 ib SUB r/m32,imm8 2/7 Subtract sign-extended immediate byte from r/m dword
//  i rm v-16/32            sub_i2rm_bv
make_instr_impl_2op(sub,i,rm,bv);