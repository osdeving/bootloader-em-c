/*
Exemplo simples de bootcode usando o gcc.
ex5.c - 28/05/2014
 
 Este exemplo é a versão C de ex3.S

*** veja ex3.S.
*** veja ex4.c para saber como compilar
*/
__asm__(".code16gcc");
__asm__("\nmovw $0x8000, %sp; jmpl $0, $main\n\t");

#define ASM __asm__ __volatile__
__attribute__((always_inline)) void puts16(const char* s)
{
	while(*s)
	{
		// Até aqui é tudo conhecido. A linha a seguir talvez seja novidade.
		// O assembly inline do gcc permite que o programador "jogue" o valor de
		// uma variável C pra dentro do bloco asm. Quando tiver um "a", vai
		// colocar o valor em ax, quando tiver um "b", colocará o valor em bx,
		// etc..Basicamente é: ax=*s e bx=7.
		// Não podemos esquecer de colocar 0xE em AH.
		// Em asm inline é usado dois '%' em vez de um. Apenas um '%' 
		// indica valores "jogados" pra dentro do bloco que não foram colocados
		// em um registrador. Usar %0 acessa o prmeiro valor, usar %1, acessa o
        // segundo, etc..
		// Não tem como falar de asm-inline em um comentário, né? Então
		// divirta-se neste link:
		// http://ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html
		// (online em 28/05/2014; tomara esteja online pra você)
		ASM("int $0x10\n\t" :: "a"(*s|0x0E00), "b"(7));
		s++;
	}
}

void main()
{
	puts16("Osdeving, Americana - SP");
	
	for(;;);
	
// PS: agora ficou com mais jeitão de C, né?
}