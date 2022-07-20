	.file	"4-3.c"
	.text
	.globl	fact
	.type	fact, @function
fact:
.LFB22:
	.cfi_startproc
	cmpq	$1, %rdi
	jle	.L3
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	leaq	-1(%rdi), %rdi
	call	fact
	imulq	%rbx, %rax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
.L3:
	.cfi_restore 3
	movl	$1, %eax
	ret
	.cfi_endproc
.LFE22:
	.size	fact, .-fact
	.globl	main
	.type	main, @function
main:
.LFB23:
	.cfi_startproc
	movl	$0, %eax
	ret
	.cfi_endproc
.LFE23:
	.size	main, .-main
	.ident	"GCC: (Arch Linux 9.3.0-1) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
