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
        print_asm_1("jmp", "", 1 + data_size / 8, &rel);

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
        
        print_asm_1("jmp", "", 2, &rel);

        cpu.eip += offset;

        return 2;//此处为2不为1+data_size/8
}

//ff /4
make_instr_func(jmp_near_indirect)
{
        OPERAND rm;
        
        rm.sreg = SREG_CS;
        rm.data_size = data_size;
        //rm.addr = eip + 1;
        int len = 1;
        len += modrm_rm(eip + 1, &rm);

        operand_read(&rm);

        int offset = sign_ext(rm.val, data_size);
        
        print_asm_1("jmp", "", 1 + data_size / 8, &rel);

        cpu.eip += offset;

        return len;
}
















