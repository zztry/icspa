#include "cpu/intr.h"
#include "cpu/instr.h"
#include "memory/memory.h"

void raise_intr(uint8_t intr_no)
{
#ifdef IA32_INTR
	//printf("Please implement raise_intr()");
	//fflush(stdout);
	//assert(0);


    // Push EFLAGS, CS, and EIP
    OPERAND m;
    m.type = OPR_MEM;
    m.sreg = SREG_SS;

    cpu.esp-=4;
    m.data_size = 32;
    m.addr = cpu.esp;
    m.val = cpu.eflags.val;
    operand_write(&m);

    cpu.esp-=4;
    m.data_size = 32;
    m.addr = cpu.esp;
    m.val = cpu.cs.val;
    operand_write(&m);

    cpu.esp-=4;
    m.data_size = 32;
    m.addr = cpu.esp;
    m.val = cpu.eip;
    operand_write(&m);

    GateDesc* gate = (void *)(page_translate( segment_translate(cpu.idtr.base + intr_no*8 , SREG_CS) )+hw_mem);    

    if(gate->type ==  INTERRUPT_GATE_32){
        cpu.eflags.IF = 0; 
    }

    uint32_t offset = (gate->offset_31_16 << 16) + gate->offset_15_0;
    cpu.eip = offset;
#endif
}

void raise_sw_intr(uint8_t intr_no)
{
	// return address is the next instruction
	cpu.eip += 2;
	raise_intr(intr_no);
}
