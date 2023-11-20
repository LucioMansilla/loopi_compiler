.data
    .text
    .globl main
    .type main, @function
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $64, %rsp
    movq $0, -48(%rbp)
    movq $9, -48(%rbp)
    movq -48(%rbp),%rdi 
    movq $0,%rsi 
    call print
    movq %rax, -64(%rbp)
    movq $0, %rdi
    movq $0, %rsi
    call print
    movq $0, %rax
    jmp LABEL_RET_main
LABEL_RET_main:
    leave
    ret
    .section .note.GNU-stack,"",@progbits
