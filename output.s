.data
x:
    .long 5
    .text
    .globl multiply
    .type multiply, @function
multiply:
    pushq %rbp
    movq %rsp, %rbp
    subq $48, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq $50, x(%rip)
    movq $0, %rax
    movq -16(%rbp), %rax
    imul -32(%rbp), %rax
    movq %rax, -48(%rbp)
    movq  -48(%rbp), %rax
    jmp LABEL_RET_multiply
LABEL_RET_multiply:
    leave
    ret
    .section .note.GNU-stack,"",@progbits
    .text
    .globl main
    .type main, @function
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp
    movq $3, -16(%rbp)
    movq x(%rip), %rdi
    movq -16(%rbp), %rsi
    call multiply
    movq %rax, -32(%rbp)
    movq -32(%rbp), %rax
    movq %rax, x(%rip)
    movq x(%rip), %rdi
    movq $0, %rsi
    call print
    movq x(%rip), %rax
    jmp LABEL_RET_main
LABEL_RET_main:
    leave
    ret
    .section .note.GNU-stack,"",@progbits
