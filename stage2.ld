OUTPUT_FORMAT("binary");
ENTRY(main);
SECTIONS
{    
    . = 0x500;    
    .text : AT(0x500)
    {
        _text = .;
        *(.text);
        _text_end = .;
    }
    .data :
    {
        _data = .;
        *(.bss);
        *(.bss*);
        *(.data);
        *(.rodata*);
        *(COMMON)
        _data_end = .;
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