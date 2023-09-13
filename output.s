.section .text
.globl _start
_start:
    mov $6, %ebx
    mov $20, %ecx
    mov %ebx, %ebx
    mov $1, %eax
    int $0x80
