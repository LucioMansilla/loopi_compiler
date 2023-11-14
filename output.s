    .text
    .globl main
    .type main, @function
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $112, %rsp
    movq $4, %rax
    negq %rax
    movq %rax, -16(%rbp)
    movq -16(%rbp) , %rax
    movq %rax, -32(%rbp)
    movq $0, %rax
    movq $2, %rax
    imul $5, %rax
    movq %rax, -48(%rbp)
    movq -32(%rbp), %rax
    subq -48(%rbp), %rax
    movq %rax, -64(%rbp)
    movq -64(%rbp) , %rax
    movq %rax, -80(%rbp)
    movq $4, %rax
    negq %rax
    movq %rax, -96(%rbp)
    movq -96(%rbp), %rax
    cmpq $2, %rax
    sete %al
    movzbq %al, %rax
    movq %rax, -112(%rbp)
    testq %rax, %rax
    jz LABEL_1
    movq -32(%rbp), %rdi
    movq $0, %rsi
    call print
    movq  -32(%rbp), %rax
    leave
    ret
LABEL_1:
    .section .note.GNU-stack,"",@progbits
