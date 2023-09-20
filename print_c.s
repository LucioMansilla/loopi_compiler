	.file	"print_c.c"
	.text
	.section	.rodata
.LC0:
	.string	"%d\n"
.LC1:
	.string	"true"
.LC2:
	.string	"false"
	.text
	.globl	print
	.type	print, @function
print:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	cmpl	$0, -8(%rbp)
	je	.L2
	cmpl	$1, -8(%rbp)
	je	.L3
	jmp	.L5
.L2:
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	jmp	.L5
.L3:
	cmpl	$0, -4(%rbp)
	je	.L6
	movl	$.LC1, %edi
	call	puts
	jmp	.L8
.L6:
	movl	$.LC2, %edi
	call	puts
.L8:
	nop
.L5:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	print, .-print
	.ident	"GCC: (GNU) 13.2.1 20230728 (Red Hat 13.2.1-1)"
	.section	.note.GNU-stack,"",@progbits
