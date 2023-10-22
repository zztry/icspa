#include "cpu/instr.h"
/*
Put the implementations of `inc' instructions here.
*/


static void instr_execute_1op() 
{
	operand_read(&opr_src);
	
	
	opr_src.val = alu_add(opr_src.val,1,data_size);
	
	operand_write(&opr_src);
	
}



//FF /0 INC r/m16 Increment r/m word by 1
//FF /6 INC r/m32 Increment r/m dword by 1  inc_rm_v
make_instr_impl_1op(inc,rm,v);