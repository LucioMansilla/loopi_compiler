    .text
    .globl f
    .type f, @function
f:
    pushq %rbp
    movq %rsp, %rbp
    subq $128, %rsp
    movq $10, -16(%rbp)
    movq -16(%rbp), %rdi
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
    subq $128, %rsp
    movq $1, -32(%rbp)
    movq $1, -48(%rbp)
    movq $4, -64(%rbp)
LABEL_1:
    movq -32(%rbp), %rax
    cmpq -64(%rbp), %rax
    setl %al
    movzbq %al, %rax
    movq %rax, -80(%rbp)
    testq %rax, %rax
    jz LABEL_2
    movq -32(%rbp), %rdi
    movq $0, %rsi
    call print
    leave
    ret
    .section .note.GNU-stack,"",@progbits
    movq $0, %rax
    movq -48(%rbp), %rax
    imul -32(%rbp), %rax
    movq %rax, -96(%rbp)
    movq -96(%rbp) , %rax
    movq %rax, -48(%rbp)
    movq -32(%rbp), %rax
    addq $1, %rax
    movq %rax, -112(%rbp)
    movq -112(%rbp) , %rax
    movq %rax, -32(%rbp)
    jmp LABEL_1
LABEL_2:
    call f
    movq -48(%rbp), %rdi
    movq $0, %rsi
    call print
    leave
    ret
    .section .note.GNU-stack,"",@progbits
