.section .text
.globl _start
_start:
    mov $6, %ebx
    mov $10, %ecx
    mov %ecx, %edx
    add %ebx, %edx
    mov %edx, %esi
    add %ecx, %esi
    mov %esi, %ecx
    mov %ecx, %ebx
    mov $1, %eax
    int $0x80
