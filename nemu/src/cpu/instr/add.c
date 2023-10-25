#include "cpu/instr.h"
/*
Put the implementations of `add' instructions here.
*/
//用宏实现make_instr_impl_2op(inst_name, src_type, dest_type, suffix)  

static void instr_execute_2op() 
{
	operand_read(&opr_src);
	operand_read(&opr_dest);
	
	opr_dest.val = alu_add(opr_src.val,opr_dest.val,data_size);
	
	operand_write(&opr_dest);
	
}

//01 /r ADD r/m16,r16 2/7 Add word register to r/m word
//01 /r ADD r/m32,r32 2/7 Add dword register to r/m dword   v-16/32  add_r2rm_v
make_instr_impl_2op(add,r,rm,v);

//83 /0 ib ADD r/m16,imm8 2/7 Add sign-extended immediate byte to r/m word
//83 /0 ib ADD r/m32,imm8 2/7 Add sign-extended immediate byte to r/m dword add_i2rm_v
make_instr_impl_2op(add,i,rm,bv);

//05 iw ADD AX,imm16 2 Add immediate word to AX
//05 id ADD EAX,imm32 2 Add immediate dword to EAX add_i2a_v
make_instr_impl_2op(add,i,a,v);

//