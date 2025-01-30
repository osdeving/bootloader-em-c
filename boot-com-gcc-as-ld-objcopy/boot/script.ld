/*
script.ld - 28/05/2014

Este script permite um maior controle das seções dentro do arquivo.
*/

/* indica o "entry point" */
ENTRY(main);

/* o bloco SECTIONS permite organizar as seções (.text, .bss, .data, etc...) */
SECTIONS
{
	. = 0x7C00;          /* começa em 0x7C00 */
	.text : AT(0x7C00)   /* .text começará em 0x7C00 */
	{
		start_text = .;
		*(.text*)        /* todas seções .text* devem ser agrupadas aqui. */
		*(.dtext*)       /* todas seções .dtext* devem ser agrupadas aqui. */
		*(rodata*)       /* todas seções .rodata* devem ser agrupadas aqui. */
	}
	.data : AT(0x7C00 +(start_data - start_text))
	{
		start_data = .;
		*(.ddata*)      /* todas seções .ddata* devem ser agrupadas aqui. */
		*(.data*)       /* todas seções .data* devem ser agrupadas aqui. */
	}
	.bss : AT(0x7C00 + (start_bss - start_text))
    {
    	start_bss = .;
    	*(.dbss*)      /* todas seções .dbss* devem ser agrupadas aqui. */
		*(.bss*)       /* todas seções .bss* devem ser agrupadas aqui. */
		*(COMMON)      /* todas os COMMON devem ser agrupados aqui. */
	}
	.sig : AT(0x7DFE)    /* coloca uma seção .sig no endereço 0x7DFE (510) */
	{
		SHORT(0xAA55);   /* coloca a assinatura de boot em 0x7DFE (510). */
	}
	/* nota: a seção .sig foi inventada, não precisa ser .sig, poderia ser
	   .signature ou .sigiloso. O que importa é que ela vai ficar exatamente
	   em 0x7DFE. O que importa é que podemos jogar valores nela aqui mesmo.
	   O manual do ld tem maiores detalhes sobre linker scripts. */
} 