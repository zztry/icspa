#include "cpu/instr.h"
/*
Put the implementations of `push' instructions here.
*/

//宏make_instr_impl_1op(inst_name, src_type, suffix)
static void instr_execute_1op()
{
    cpu.esp -=data_size/8;
    
    //将src写入esp/sp的地址中
    
    //OPERAND m;
    
    //opr_src.data_size=data_size;
    operand_read(&opr_src);
    
    opr_dest.data_size = data_size;
    opr_dest.sreg = SREG_SS;
    opr_dest.type = OPR_MEM;
    opr_dest.addr = cpu.esp;
    opr_dest.val = opr_src.val;
    if(data_size==8)
    {
        opr_dest.val = sign_ext(opr_src.val,8);
    }
    operand_write(&opr_dest);
}

//50-57   r->esp 16/32 push_rm_v
make_instr_impl_1op(push,r,v);       

//FF /6 PUSH m16 5 Push memory word
//FF /6 PUSH m32 5 Push memory dword  push_m_v
make_instr_impl_1op(push,rm,v);    //没有m，只有rm

//6a push_i_b
make_instr_impl_1op(push,i,b); 

//68 push_i_v
make_instr_impl_1op(push,i,v);

/*
make_instr_func(push_r_v)
{
    OPERAND r;
    r.data_size = data_size;
    r.type = OPR_REG;
    r.addr = opcode & 0x7;

    operand_read(&opr_src);
}*/


make_instr_func(pusha)
{
    uint32_t temp = cpu.esp;
    OPERAND m;
    m.type = OPR_MEM;
    m.data_size = 32;
    m.sreg = SREG_DS;
    
        cpu.esp -= 4;
        m.addr = cpu.esp;
        m.val = cpu.eax;
        operand_write(&m);
    
        cpu.esp -= 4;
        m.addr = cpu.esp;
        m.val = cpu.ecx;
        operand_write(&m);

        cpu.esp -= 4;
        m.addr = cpu.esp;
        m.val = cpu.edx;
        operand_write(&m);

        cpu.esp -= 4;
        m.addr = cpu.esp;
        m.val = cpu.ebx;
        operand_write(&m);
     
        cpu.esp -= 4;
        m.addr = cpu.esp;
        m.val = temp;
        operand_write(&m);

        cpu.esp -= 4;
        m.addr = cpu.esp;
        m.val = cpu.ebp;
        operand_write(&m);

        cpu.esp -= 4;
        m.addr = cpu.esp;
        m.val = cpu.esi;
        operand_write(&m);

        cpu.esp -= 4;
        m.addr = cpu.esp;
        m.val = cpu.edi;
        operand_write(&m);
    
    

    return 1;
}

/*    
make_instr_func(push_r_l)//32
{
    OPERAND r1,r2,m;        // 创建源操作数和目的操作数（ESP）局部变量

    
    
    r1.data_size = 8;        // 配置源操作数大小
    r1.type = OPR_REG;       // 配置源操作数类型，通用寄存器
    r1.addr = opcode & 0x7;  // 配置源操作数地址，即寄存器地址
    
    r2.data_size = 8;    //ESP    
    r2.type = OPR_REG;       
    r2.addr = 4;  
    
    operand_read(&r2);
    r2.val = r2.val-4;      // 将源操作数的值赋给栈
    operand_write(&r2);    // esp-4
    
    m.data_size = 32; // data_size是个全局变量，表示操作数的比特长度
    m.type = OPR_MEM;
    m.addr = r2.val;
    
    operand_read(&r1);   // 读通用寄存器内的值
    operand_read(&m);
    m.val = r1.val;      // 将源操作数的值赋给栈
    operand_write(&m);    
    
    return 1;             // 返回指令长度
}*/
