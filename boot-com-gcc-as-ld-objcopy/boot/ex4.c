/*
Exemplo simples de bootcode usando o gcc.
ex4.c - 28/05/2014
 
 Este exemplo é a versão C de ex2.S

 Cria um objeto usando gcc em vez do as depois o transforma em .elf (ld)
 e logo após em .bin(objcopy).

$ gcc -c -Os -march=i686 -ffreestanding -Wall -Werror ex4.c -o ex4.o
$ ld -static -Tscript.ld -nostdlib -nmagic -o ex4.elf ex4.o
$ objcopy -O binary ex4.elf ex4.bin

 Não sou documentação ^^. Procure saber o que cada opção faz, não jogue
 o comando no terminal apenas.
 
 A opção -T permite usar um script para o ld. Veja os comentários em script.ld
 para entendê-lo melhor.
 
*** veja ex2.S.
*** veja ex1.S para saber como compilar e testar
*/

/* __asm__ permite colocar trechos assembly em códigos C.
   a sintaxe simplificada é: __asm__("instruções");
   nota: veremos maiores detalhes de __asm__ no próximo exemplo. */
__asm__(".code16\n\t");

// salta pra função main
__asm__("jmpl $0, $main\n\t");

// __volatile__ avisa o gcc pra não modificar (otimizar?) nossas instruções.
#define ASM __asm__ __volatile__

void main()
{
	// se não usar \n\t vai ficar tudo junto e dará erro de sintaxe no as.
	// usar ';' também funciona.
	ASM("movb $'J', %al\n\t"
		"movb $0x0E, %ah\n\t"
		"int $0x10\n\t");

	ASM("movb $'u', %al\n\t"
		"movb $0x0E, %ah\n\t"
		"int $0x10\n\t");
		
	
	// só pra não esquecer que estamos programando em C ^^
	for(;;); // <-- ASM("jmp .");
	
// PS: quem disse que bootloaders só podem ser feitos em assembly?
}