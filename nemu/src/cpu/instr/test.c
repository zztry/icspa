#include "cpu/instr.h"
/*
Put the implementations of `test' instructions here.
*/

//用宏实现make_instr_impl_2op(inst_name, src_type, dest_type, suffix)  

static void instr_execute_2op() 
{
	operand_read(&opr_src);
	operand_read(&opr_dest);
	//不能保证高位？
	//opr_dest.val = sign_ext(opr_dest.val,opr_dest.data_size);
	//opr_src.val = sign_ext(opr_src.val,opr_src.data_size); 
	
	alu_and(opr_src.val,opr_dest.val,data_size);
	//
	
	/*
	opr_dest.val = alu_and(opr_src.val,opr_dest.val,data_size);
	operand_write(&opr_dest);*/
	
}

//85 /r TEST r/m16,r16 2/5 AND word register with r/m word
//85 /r TEST r/m32,r32 2/5 AND dword register with r/m dword   v 16/32 test_r2rm_v
make_instr_impl_2op(test,r,rm,v);

//84
make_instr_impl_2op(test,r,rm,b);

//f7 /0   test_i2rm_v
make_instr_func(test,i,rm,v);



/*
make_instr_func(test_r2rm_l)//32->32
{
    
    //cpu.eflags.CF=0;
    //cpu.eflags.OF=0;
    
    //OPERAND rm;//源，目的 操作数
    
    //rm.data_size = data_size; // data_size是个全局变量，表示操作数的比特长度
    //int len = 1;                          // opcode 长度1字节
    //len += modrm_rm(eip + 1, &rm); // 读ModR/M字节，rm的type和addr会被填写
    
    
    return 2;
}*/
