/*
stage2.c - 02/06/2014 by osdeving from America-SP, Brazil

* Main file for stage2. 
* Loads kernel of a floppy disk formatted with FAT12.

*/

#include "boot.h"

// setup segment registers
__asm__(
"cli\n\t"
"xorw %ax, %ax\n\t"
"movw %ax, %ds\n\t"
"movw %ax, %es\n\t"
"movw %ax, %fs\n\t"
"movw %ax, %gs\n\t"
"movw %ax, %ss\n\t"
"movl $0xA000, %esp\n\t"
"sti\n\t"
"jmpl $0, $main\n\t");

//data ring0 and code ring0
// #define OS_CODE_DESC 0x08
// #define OS_DATA_DESC 0x10

// #define NR_GDT_DESCRIPTORS 3

//struct for gdt entry
// typedef struct __PACKED _gdt_entry
// {
	// word limit;
	// word base_lo;
	// byte base_mid;
	// byte type;
	// byte gran;
	// byte base_hi;
// } gdt_entry_t;

uint64 *gdt = ((uint64 *)0);

void __NOINLINE __REGPARM puts16(const char* s)
{
	while(*s)
	{
		__ASM("int $0x10\n\t" :: "a"(*s|0x0E00), "b"(7));
		s++;
	}
}

// err.. update segments with new_code and new_data
static void gdt_update_segments(dword new_code, dword new_data)
{
	__ASM("pushl %0\n\t"
        "pushl $1f\n\t"
        "lret \n\t"
        "1:\n\t"
        "mov %1, %%eax\n\t"
        "mov %%ax, %%ds\n\t"
        "mov %%ax, %%es\n\t"
        "mov %%ax, %%fs\n\t"
        "mov %%ax, %%gs\n\t"
        "mov %%ax, %%ss\n\t"
       :
       : "g" (new_code), "g" (new_data)
       : "eax");
}

// loads a new gdt
/*static void __NOINLINE load_gdt(void* base, word size)
{
	struct
    {
		word length;
		dword base;
    } __PACKED gdtr;

    gdtr.length = size;
    gdtr.base = 0x90000;
	
   __ASM("lgdt (%0)\n\t" :: "r"(&gdtr));
}*/

void main()
{
	byte failed = 0;
	
	// enalbe A20 using BIOS 15,2401
	__ASM("int $0x15\n\t"
		  "setcb %0\n\t"
		: "=m"(failed) : "a"(0x2401));
		
	if(failed)
	{
		puts16("Error: enable A20 using BIOS 15,2401");
		for(;;);
	}
	
	// intialize 3 entries, null, code and data. (model flat)
	gdt[0] = 0;
	gdt[1] = 0x00CF9A000000FFFF;
	gdt[2] = 0x00CF92000000FFFF;
	
	struct { word length; dword base; } __PACKED gdtr;
    gdtr.length = 23;
    gdtr.base = 0;
	 
	 __ASM("lgdt (%0)\n\t" :: "r"(&gdtr));
	
	// enable PE bit
	__ASM("movl %cr0, %eax\n\t"
		  "orl $1, %eax\n\t"
		  "movl %eax, %cr0\n\t");
		  
	// enter to protected model
	gdt_update_segments(0x08, 0x10);
	__ASM("jmpl $8, $pmode\n\t");
}

// this function is in protected mode!
__asm__(".code32");
void __NORETURN pmode()
{
	((word*)0xB8000)[0] = 0x0F41;
	
	while(1);
}