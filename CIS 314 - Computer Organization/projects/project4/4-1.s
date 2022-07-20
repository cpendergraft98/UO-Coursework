	.file	"4-1.c"
	.text
	.globl	loop
	.type	loop, @function
loop:
.LFB39:
	.cfi_startproc
	endbr64
	movq	%rsi, %rcx
	movl	$1, %eax
	movl	$0, %edx
.L2:
	testq	%rax, %rax
	je	.L4
	movq	%rax, %r8
	andq	%rdi, %r8
	orq	%r8, %rdx
	salq	%cl, %rax
	jmp	.L2
.L4:
	movq	%rdx, %rax
	ret
	.cfi_endproc
.LFE39:
	.size	loop, .-loop
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Executing test1."
.LC1:
	.string	"Test1 output: %ld\n"
.LC2:
	.string	"Executing test2."
.LC3:
	.string	"Test2 output: %ld\n"
.LC4:
	.string	"Executing test3. "
.LC5:
	.string	"Test3 output: %ld\n"
.LC6:
	.string	"Executing test4. "
.LC7:
	.string	"Executing test5. "
.LC8:
	.string	"Test5 output: %ld\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB40:
	.cfi_startproc
	endbr64
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	leaq	.LC0(%rip), %rdi
	call	puts@PLT
	movl	$5, %esi
	movl	$1, %edi
	call	loop
	movq	%rax, %rdx
	leaq	.LC1(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	leaq	.LC2(%rip), %rdi
	call	puts@PLT
	movl	$4, %esi
	movl	$2, %edi
	call	loop
	movq	%rax, %rdx
	leaq	.LC3(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	leaq	.LC4(%rip), %rdi
	call	puts@PLT
	movl	$3, %esi
	movl	$3, %edi
	call	loop
	movq	%rax, %rdx
	leaq	.LC5(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	leaq	.LC6(%rip), %rdi
	call	puts@PLT
	movl	$2, %esi
	movl	$4, %edi
	call	loop
	movq	%rax, %rdx
	leaq	.LC1(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	leaq	.LC7(%rip), %rdi
	call	puts@PLT
	movl	$1, %esi
	movl	$5, %edi
	call	loop
	movq	%rax, %rdx
	leaq	.LC8(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	movl	$0, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE40:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
