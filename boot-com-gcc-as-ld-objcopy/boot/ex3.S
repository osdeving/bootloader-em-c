/*
Exemplo simples de bootcode usando o gas.
ex3.S - 28/05/2014
 
Este exemplo usa um laço para imprimir uma string terminada em zero.

*** veja ex2.S para saber como imprimir um único caracter.
*** veja ex1.S para saber como compilar e testar
*/ 

.code16
.text
.global _start

_start:
	
	// move 'nome' pasa SI e chama a função puts16
	movw $nome, %si
	call puts16
	
	// again
	movw $cidade, %si
	call puts16
	
	// again again
	movw $uf, %si
	call puts16
	
	jmp . 

// Imprime a string que estiver no endereço ES:SI
// O laço loopstring para quando encontrar 0 em AL
// LODSB obtém o byte em ES:SI e coloca em AL incrementando SI depois.
// OR liga ZF apenas quando ambos operandos forem 0, isto é, AL for 0
// JZ salta se o bit ZF for 1, isto é, se OR ligar ZF.
puts16:
loopstring:
	lodsb
	or %al, %al
	jz done
	movb $0x0E, %ah
	int $0x10
	jmp loopstring
done:
	ret

// .asciz define uma cadeia de caracteres e adiciona NULL no final
// nota: no nasm seria: nome: db "Osdeving", 0
nome: .asciz "\n\rOsdeving, "

// .ascii não adiciona NULL no final
// nota: no nasm seria: cidade: db "Osdeving"
// nota2: podemos usar os escapes \n, \r, \0, \\, \t, etc...
cidade: .ascii "Americana - \0"

// define 3 bytes, tal como db faz no nasm.
uf: .byte 'S', 'P', 0

	. = _start + 510
	.byte 0x55
	.byte 0xAA
