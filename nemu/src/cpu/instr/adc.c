#include "cpu/instr.h"
/*
Put the implementations of `adc' instructions here.
*/

static void instr_execute_2op() 
{
	operand_read(&opr_src);
	
	operand_read(&opr_dest);
	opr_src.val = sign_ext(opr_src.val,opr_src.data_size);
	//opr_dest.val = sign_ext(opr_dest.val,opr_dest.data_size);
	opr_dest.val = alu_adc(opr_src.val,opr_dest.val,data_size);
	operand_write(&opr_dest);
	
}


//11  adc_r2rm_v
make_instr_impl_2op(adc,r,rm,v);

//10  adc_r2rm_b
make_instr_impl_2op(adc,r,rm,b);

//12  adc_rm2r_b
make_instr_impl_2op(adc,rm,r,b);

//13
make_instr_impl_2op(adc,rm,r,v);

//14  adc_i2a_b
make_instr_impl_2op(adc,i,a,b);

//15
make_instr_impl_2op(adc,i,a,v);

//80 /2   adc_i2rm_b
make_instr_impl_2op(adc,i,rm,b);

//81 /2
make_instr_impl_2op(adc,i,rm,v);

//83 /2
make_instr_impl_2op(adc,i,rm,bv);








