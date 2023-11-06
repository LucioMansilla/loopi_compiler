    .text
    .globl sum
    .type sum, @function
sum:
    pushq %rbp
    movq %rsp, %rbp
    subq $96, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq -16(%rbp), %rax
    cmpq $1, %rax
    setl %al
    movzbq %al, %rax
    movq %rax, -48(%rbp)
    testq %rax, %rax
    jz LABEL_1
    movq $0, %rdi
    movq $0, %rsi
    call print
    movq $0, %rax
    leave
    ret
LABEL_1:
    movq -16(%rbp), %rax
    subq $1, %rax
    movq %rax, -64(%rbp)
    movq -64(%rbp),%rdi 
    movq -32(%rbp),%rsi 
    call sum
    movq %rax, -80(%rbp)
    movq -80(%rbp), %rax
    addq -32(%rbp), %rax
    movq %rax, -96(%rbp)
    movq -96(%rbp), %rdi
    movq $0, %rsi
    call print
    movq  -96(%rbp), %rax
    leave
    ret
    .section .note.GNU-stack,"",@progbits
    .text
    .globl main
    .type main, @function
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $112, %rsp
    movq $0, %rax
    movq $1, %rax
    imul $1, %rax
    movq %rax, -16(%rbp)
    movq -16(%rbp) , %rax
    movq %rax, -32(%rbp)
    movq $5, %rax
    subq $1, %rax
    movq %rax, -48(%rbp)
    movq -48(%rbp) , %rax
    movq %rax, -64(%rbp)
    movq $1, -80(%rbp)
    movq $5,%rdi 
    movq $5,%rsi 
    call sum
    movq %rax, -96(%rbp)
    movq -96(%rbp) , %rax
    movq %rax, -112(%rbp)
    movq -112(%rbp), %rdi
    movq $0, %rsi
    call print
    movq  -112(%rbp), %rax
    leave
    ret
    .section .note.GNU-stack,"",@progbits
