#include "cpu/instr.h"


//e9 官方写好的
make_instr_func(jmp_near)
{
        OPERAND rel;
        rel.type = OPR_IMM;
        rel.sreg = SREG_CS;
        rel.data_size = data_size;
        rel.addr = eip + 1;

        operand_read(&rel);

        int offset = sign_ext(rel.val, data_size);
        // thank Ting Xu from CS'17 for finding this bug
        print_asm_1("jmp1", "", 1 + (data_size / 8), &rel);

        cpu.eip += offset;

        return 1 + data_size / 8;
}

//eb  8位 jmp_short EB cb JMP rel8 7+m Jump short
make_instr_func(jmp_short)
{
        OPERAND rel;
        rel.type = OPR_IMM;
        rel.sreg = SREG_CS;
        rel.data_size = 8;
        rel.addr = eip + 1;

        operand_read(&rel);
        
        int offset = sign_ext(rel.val, rel.data_size);
        
        print_asm_1("jmp2", "", 2, &rel);

        cpu.eip += offset;

        return 2;
}

//ff /2
make_instr_func(jmp_near_indirect)
{
        OPERAND rm;
        
        rm.data_size = data_size;
        rm.sreg = SREG_CS;
        int len = 1;
        len += modrm_rm(eip + 1, &rm);

        operand_read(&rm);
        if(data_size==16)
        {
            cpu.eip =rm.val&0xffff;
        }
        else
        {
            cpu.eip = rm.val;
        }
        
        
        print_asm_1("jmp3", "", 1 + data_size / 8, &rm);

        //绝对地址跳转，返回0

        return 0;
}


//ea
make_instr_func(jmp_far_imm)
{
        OPERAND rel;
        rel.type = OPR_IMM;
        rel.sreg = SREG_CS;
        rel.data_size = 32;
        rel.addr = eip + 1;

        operand_read(&rel);

        if(data_size==16)
        {
            cpu.eip = rel.val&0xffff;
        }
        else
        {
            cpu.eip = rel.val;
        }
        rel.data_size = 16;
        rel.addr += data_size/8;
        operand_read(&rel);
        
        cpu.cs.val = rel.val;
        load_sreg(1);
        
        print_asm_1("jmp4", "", 1 + data_size / 8, &rel);
        return 0;
}













