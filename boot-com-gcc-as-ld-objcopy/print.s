.print:
//  pusha   ::  aqui minha dúvida! Na arquitetura 64bits o pusha/popa n existe !!
    movb (%si), %al
    inc %si
    or %al, %al
    jz .done
    mov $0x0e, %ah
    int $0x10
    jmp .print
.done:
//  popa 
    ret


.clear:
//  pusha
    mov $0x0003, %ax
    int $0x10
//  popa
    ret
