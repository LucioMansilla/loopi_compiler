    .text
    .globl sum
    .type sum, @function
sum:
    pushq %rbp
    movq %rsp, %rbp
    subq $48, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq -16(%rbp), %rax
    addq -32(%rbp), %rax
    movq %rax, -48(%rbp)
    movq -48(%rbp), %rdi
    movq $0, %rsi
    call print
    leave
    ret
    .section .note.GNU-stack,"",@progbits
    .text
    .globl main
    .type main, @function
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $64, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq $10, -48(%rbp)
    movq $20, -64(%rbp)
    movq $3000, -16(%rbp)
    movq -16(%rbp), %rdi
    movq $0, %rsi
    call print
    leave
    ret
    .section .note.GNU-stack,"",@progbits
