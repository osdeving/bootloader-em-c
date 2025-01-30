OUTPUT_FORMAT("binary");
ENTRY(main);
SECTIONS
{    
    . = 0x7C00;    
    .text : AT(0x7C00)
    {
		*(bpb);
		*(start);
        *(.text);
    }
    .data :
    {
        *(.bss);
        *(.bss*);
        *(.data);
        *(.rodata*);
        *(COMMON)
    }    
    .sig : AT(0x7DFE)    
    {        
        SHORT(0xaa55);
    }   
    /DISCARD/ :
    {
		*(.eh_frame);
        *(.note*);
        *(.iplt*);
        *(.igot*);
        *(.rel*);
        *(.comment);
    }
}