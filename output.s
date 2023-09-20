    .text
    .globl main
    .type main, @function
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
    movq $10, -8(%rbp)
    movq $2, %rax
    addq $5, %rax
    movq %rax, 0(%rbp)
    movq 0(%rbp), %rax
    movq %rax, %rdi
    movq $0, %rsi
    call print
    addq $16, %rsp
    popq  %rbp
    ret
    .section	.note.GNU-stack,"",@progbits
