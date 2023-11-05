#include "common.h"
#include "memory.h"
#include "string.h"

#include <elf.h>

#ifdef HAS_DEVICE_IDE
#define ELF_OFFSET_IN_DISK 0
#endif

#define STACK_SIZE (1 << 20)

void ide_read(uint8_t *, uint32_t, uint32_t);
void create_video_mapping();
uint32_t get_ucr3();

uint32_t loader()
{
	Elf32_Ehdr *elf;
	Elf32_Phdr *ph, *eph;

#ifdef HAS_DEVICE_IDE   
	uint8_t buf[4096];
	ide_read(buf, ELF_OFFSET_IN_DISK, 4096);
	elf = (void *)buf;
	Log("ELF loading from hard disk.");  
#else
	elf = (void *)0x0;
	Log("ELF loading from ram disk.");
#endif

	/* Load each program segment */
	ph = (void *)elf + elf->e_phoff;   //程序头表的起始地址
	eph = ph + elf->e_phnum;            //程序头表结束地址
	for (; ph < eph; ph++)
	{
		if (ph->p_type == PT_LOAD)
		{

			// remove this panic!!!
			//panic("Please implement the loader");

/* TODO: copy the segment from the ELF file to its proper memory area */
            //从文件Offset开始位置，连续FileSiz个字节的内容需要被装载
            for(uint32_t i = 0;i<ph->p_filesz;i++)
            {
                memcpy((ph->p_offset+i), (ph->p_vaddr+i), 8);
                //hw_mem[ph->p_vaddr+i] = hw_mem[ph->p_offset+i];
            }
            
/* TODO: zeror the memory area [vaddr + file_sz, vaddr + mem_sz) */
            //装载到内存VirtAddr开始，连续MemSiz个字节的区域中 ，mem_sz - file_sz大小的位置为0
            memset(ph->p_vaddr+ph->p_filesz, 0, (ph->p_memsz - ph->p_filesz) );
            /*for(uint32_t i = ph->p_filesz;i<ph->p_memsz;i++)
            {
                //memset(hw_mem, 0, MEM_SIZE_B);
                memset(hw_mem+i, 0, 8);
                //hw_mem[ph->p_vaddr+i] = 0;
            }*/
            
#ifdef IA32_PAGE
			/* Record the program break for future use */
			extern uint32_t brk;
			uint32_t new_brk = ph->p_vaddr + ph->p_memsz - 1;
			if (brk < new_brk)
			{
				brk = new_brk;
			}
#endif
		}
	}

	volatile uint32_t entry = elf->e_entry;//程序入口地址

#ifdef IA32_PAGE
	mm_malloc(KOFFSET - STACK_SIZE, STACK_SIZE);
#ifdef HAS_DEVICE_VGA
	create_video_mapping();
#endif
	write_cr3(get_ucr3());
#endif
	return entry;
}
