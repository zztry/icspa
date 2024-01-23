#include "cpu/intr.h"
#include "cpu/instr.h"

/*
Put the implementations of `int' instructions here.

Special note for `int': please use the instruction name `int_' instead of `int'.
*/
make_instr_func(int_)
{
    OPERAND rel;
    rel.type = OPR_IMM;
    rel.data_size = 8;
    rel.sreg = SREG_CS;
    rel.addr = eip+1;
    operand_read(&rel);
    raise_sw_intr(rel.val);
    return 0;
}
