/*
Exemplo simples de bootcode usando o gas.
ex2.S - 28/05/2014
 
Este exemplo imprime um caracter usando a INT 10,0E. Mais detalhes em:
http://stanislavs.org/helppc/ 
ou
http://panthema.net/2006/helppc21/HelpPC-2.10-HTML/

*** veja ex1.S para saber como compilar e testar.
*** o arquivo ex1.S também contém comentários que estão ausentes em ex2.S
*/ 

.code16
.text
.global _start

_start:
	
	// imprime a letra 'J' na tela
	// nota: constantes precisam do prefixo $
	// nota2: é src -> dest e não dest <- src como no nasm.
	// nota3: o sufixo de tamanho é b, w, l.
	// obs: No nasm não é sufixo, é uma diretiva isolada: byte, word e dword.
	movb $'J', %al
	movb $0x0E, %ah
	int $0x10
	
	// imprime outra letra.
	// a INT 10,0E move o cursor (teletype mode, seja lá o que for teletype)
	movb $'u', %al
	movb $0x0E, %ah
	int $0x10
	
	jmp . 
	
	. = _start + 510
	
	.byte 0x55
	.byte 0xAA
