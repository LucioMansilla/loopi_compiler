    .text
    .globl main
    .type main, @function
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp
    movq $10, -8(%rbp)
    movq $0, -16(%rbp)
    movq $10, -24(%rbp)
    movq -24(%rbp), %rax
    addq -8(%rbp), %rax
    movq %rax, -32(%rbp)
    movq -32(%rbp), %rax
    movq %rax, %rdi
    movq $1, %rsi
    call print
    addq $32, %rsp
    popq  %rbp
    ret
