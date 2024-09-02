#include "cpu/instr.h"
#include "device/port_io.h"
/*
Put the implementations of `in' instructions here.
*/
make_instr_func(in_b)
{
    //OPERAND r;

    //r.data_size = 8;
    //r.type = OPR_REG;
    //r.addr = 0x2;
    //operand_read(&r);

    cpu.eax = pio_read(cpu.edx,1);

    return 1;
}

make_instr_func(in_v)
{
    /*OPERAND r;

    r.data_size = data_size;
    r.type = OPR_REG;
    r.addr = 0x2;
    operand_read(&r);*/

    cpu.eax = pio_read(cpu.edx,data_size/8);

    return 1;
}
