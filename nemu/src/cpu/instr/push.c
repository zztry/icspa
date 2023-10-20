#include "cpu/instr.h"
/*
Put the implementations of `push' instructions here.
*/

make_instr_func(push_r_l)//32
{
    OPERAND r1,r2,m;        // 创建源操作数和目的操作数（ESP）局部变量

    
    
    r1.data_size = 8;        // 配置源操作数大小
    r1.type = OPR_REG;       // 配置源操作数类型，通用寄存器
    r1.addr = opcode & 0x7;  // 配置源操作数地址，即寄存器地址
    
    r2.data_size = 8;    //ESP    
    r2.type = OPR_REG;       
    r2.addr = &cpu.gpr[4];  
    
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
    
    return 2;             // 返回指令长度
}