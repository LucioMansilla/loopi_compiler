.section .text
.globl _start
_start:
    mov $5, %ebx
    mov $10, %ebx
    mov %ebx, %ebx
    mov $1, %eax
    int $0x80
