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
	Log("test");
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
            uint32_t p_paddr = 0;
#ifdef IA32_PAGE
            p_paddr = mm_malloc(ph->p_vaddr,ph->p_memsz);
            Log(" vaddr = %x  paddr = %x",ph->p_vaddr,p_paddr);
            memcpy((void *)p_paddr, (void *)(ph->p_offset), ph->p_filesz); 
            if(ph->p_memsz>ph->p_filesz)
            {
                memset((void *)(p_paddr+ph->p_filesz), 0, (ph->p_memsz - ph->p_filesz) );
            }
#else
            Log(" vaddr = %x",ph->p_vaddr);
            memcpy((void *)(ph->p_vaddr), (void *)(ph->p_offset), ph->p_filesz); 
            if(ph->p_memsz>ph->p_filesz)
            {
                memset((void *)(ph->p_vaddr+ph->p_filesz), 0, (ph->p_memsz - ph->p_filesz) );
            }
#endif

/* TODO: copy the segment from the ELF file to its proper memory area */
            //从文件Offset开始位置，连续FileSiz个字节的内容需要被装载
            
            
            
/* TODO: zeror the memory area [vaddr + file_sz, vaddr + mem_sz) */
            
            
            
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
