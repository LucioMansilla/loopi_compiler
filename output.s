    .text
    .globl main
    .type main, @function
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $96, %rsp
    movq $4, -48(%rbp)
    movq $0, -64(%rbp)
    movq -48(%rbp),%rdi 
    movq $0,%rsi 
    call print
    movq %rax, -80(%rbp)
    movq -64(%rbp), %rax
    cmpq $0, %rax
    sete %al
    movzbq %al, %rax
    movq %rax, -96(%rbp)
    testq %rax, %rax
    jz LABEL_1
    movq $10, -48(%rbp)
LABEL_1:
    movq -48(%rbp), %rdi
    movq $0, %rsi
    call print
    movq  -48(%rbp), %rax
    leave
    ret
    .section .note.GNU-stack,"",@progbits
