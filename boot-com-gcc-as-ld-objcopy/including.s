.code16

.text
.global _start


_start:


    call .clear

    mov $MSG, %si
    call .print

    jmp .


.include "print.s"
MSG: .asciz "Welcome !!!"

    . = _start + 510

    .byte 0x55
    .byte 0xAA
