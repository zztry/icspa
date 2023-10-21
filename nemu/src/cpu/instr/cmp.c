#include "cpu/instr.h"
/*
Put the implementations of `cmp' instructions here.
*/

//用宏实现make_instr_impl_2op(inst_name, src_type, dest_type, suffix)  

static void instr_execute_2op() 
{
	operand_read(&opr_src);
	//opr_dest.val = opr_src.val;
	operand_read(&opr_dest);
	
	opr_dest.val = sign_ext(opr_dest.val,opr_dest.data_size);
	opr_src.val = sign_ext(opr_src.val,opr_src.data_size);
	//src-dest 根据sub 是不是反了？
	alu_sub(opr_dest.val,opr_src.val,data_size);
	
}

//83 src为imm8   dest为r/m 16/32   bv – 源操作数为8位，目的操作数为16/32位
make_instr_impl_2op(cmp,i,rm,bv);
/*
make_instr_func(cmp_i2rm_bv) //8->16/32
{
    OPERAND rm,imm;
    
    rm.data_size = data_size; // data_size是个全局变量，表示操作数的比特长度
    int len = 1;                          // opcode 长度1字节
    len += modrm_rm(eip + 1, &rm); // 读ModR/M字节，rm的type和addr会被填写
    
    imm.type = OPR_IMM;        // 填入立即数类型
    imm.addr = eip + len;           // 找到立即数的地址
    imm.data_size = data_size;  
    
    operand_read(&rm);
    operand_read(&imm);
    int32_t result = sign_ext(rm.val, data_size)-sign_ext(imm.val, 8) ;
    
    if(result==0)
    {
        cpu.eflags.ZF=1;
    }
    else
    {
        cpu.eflags.ZF=0;
    }
    
    if(result>=0)
    {
        cpu.eflags.CF=0;
    }
    else
    {
        cpu.eflags.CF=1;
    }
    
    return len + 1;    // opcode长度 + ModR/M字节扫描长度 + 立即数长度,这里为1
    

}*/


make_instr_func(cmp_i2r_b)//8 i->al;
{
    OPERAND r,imm;
    
    r.data_size = data_size; // data_size是个全局变量，表示操作数的比特长度
    int len = 1;                          // opcode 长度1字节
    r.type = OPR_REG; 
    r.addr = 0;//al寄存器
    
    imm.type = OPR_IMM;        // 填入立即数类型
    imm.addr = eip + len;           // 找到立即数的地址
    imm.data_size = 8;  //8字节
    
    operand_read(&r);
    operand_read(&imm);
    int32_t result = sign_ext(r.val, data_size)-sign_ext(imm.val, 8) ;
    
    if(result==0)
    {
        cpu.eflags.ZF=1;
    }
    else
    {
        cpu.eflags.ZF=0;
    }
    
    if(result>=0)
    {
        cpu.eflags.CF=0;
    }
    else
    {
        cpu.eflags.CF=1;
    }
    
    return len + 1;    // opcode长度 + ModR/M字节扫描长度 + 立即数长度,这里为1
}