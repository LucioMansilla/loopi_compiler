    .text
    .globl main
    .type main, @function
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $176, %rsp
    movq $0, -32(%rbp)
    movq $1, -48(%rbp)
    movq -32(%rbp), %rax
    cmpq -48(%rbp), %rax
    sete %al
    movzbq %al, %rax
    movq %rax, -64(%rbp)
    movq -64(%rbp),%rdi 
    call print_bool
    movq %rax, -80(%rbp)
    movq -32(%rbp), %rax
    cmpq $1, %rax
    sete %al
    movzbq %al, %rax
    movq %rax, -96(%rbp)
    movq -96(%rbp),%rdi 
    call print_bool
    movq %rax, -112(%rbp)
    movq $2, %rax
    cmpq -48(%rbp), %rax
    sete %al
    movzbq %al, %rax
    movq %rax, -128(%rbp)
    movq -128(%rbp),%rdi 
    call print_bool
    movq %rax, -144(%rbp)
    movq $1, %rax
    cmpq $2, %rax
    sete %al
    movzbq %al, %rax
    movq %rax, -160(%rbp)
    movq -160(%rbp),%rdi 
    call print_bool
    movq %rax, -176(%rbp)
    movq $0, %rdi
    movq $0, %rsi
    call print
    movq $0, %rax
    leave
    ret
    .section .note.GNU-stack,"",@progbits
