/*
 * Tive problemas na compilação dos codigos em C. Acho que vou precisar 
 * do cross-comppiler mesmo. Ele acusa que estou escolher uma arquitetura
 * incompatível. (i686)
 */

.code16
.text
.global _start


_start: 
    movw $0x0003, %ax
    int $0x10

    push $'A'
    push $'B'
    push $'C'

    mov $2, %cx
.loop:
    movb $0x0e, %ah
    pop %bx
    movb %bl, %al
    int $0x10
    or %cx, %cx
    jz .done
    dec %cx
    jmp .loop
.done:
    jmp .


    . = _start+510

    .byte 0x55
    .byte 0xAA
