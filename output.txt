.LC0:
    .globl main
    .ascii "Hello World\0"
main:
    subq    $40, %rsp
    leaq    .LC0(%rip), %rcx
    call    printf
    addq    $40, %rsp
    ret
