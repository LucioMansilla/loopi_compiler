    .text
    .globl main
    .type main, @function
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $64, %rsp
    movq $4, %rax
    negq %rax
    movq %rax, -16(%rbp)
    movq -16(%rbp) , %rax
    movq %rax, -32(%rbp)
    movq $4, %rax
    negq %rax
    movq %rax, -48(%rbp)
    movq -48(%rbp), %rax
    cmpq -32(%rbp), %rax
    sete %al
    movzbq %al, %rax
    movq %rax, -64(%rbp)
    testq %rax, %rax
    jz LABEL_1
    movq $10, -32(%rbp)
LABEL_1:
    movq -32(%rbp), %rdi
    movq $0, %rsi
    call print
    movq  -32(%rbp), %rax
    leave
    ret
    .section .note.GNU-stack,"",@progbits
