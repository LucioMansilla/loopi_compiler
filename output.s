.section .text
.globl _start
_start:
    mov $3, %ebx
    mov $1, %edx
    add $5, %r8d
    mov %r8d, %edi
    mov %edi, %ebx
    mov $1, %eax
    int $0x80
