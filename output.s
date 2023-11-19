.data
y:
    .long 5
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
    movq  -48(%rbp), %rax
    jmp LABEL_RET_sum
LABEL_RET_sum:
    leave
    ret
    .section .note.GNU-stack,"",@progbits
    .text
    .globl main
    .type main, @function
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $48, %rsp
    movq $0, -16(%rbp)
    movq $1,%rdi 
    movq $2,%rsi 
    call sum
    movq %rax, -32(%rbp)
    movq -32(%rbp), %rax
    addq y(%rip), %rax
    movq %rax, -48(%rbp)
    movq -48(%rbp) , %rax
    movq %rax, -16(%rbp)
    movq -16(%rbp), %rdi
    movq $0, %rsi
    call print
    movq  -16(%rbp), %rax
    jmp LABEL_RET_main
LABEL_RET_main:
    leave
    ret
    .section .note.GNU-stack,"",@progbits
