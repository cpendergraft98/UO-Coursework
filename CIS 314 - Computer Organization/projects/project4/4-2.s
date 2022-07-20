	.file	"4-2.c"
	.text
	.globl	sum
	.type	sum, @function
sum:
.LFB22:
	.cfi_startproc
#APP
# 82 "4-2.c" 1
	movq %rdi, %rdi # from in rdi;
# 0 "" 2
# 83 "4-2.c" 1
	movq %rsi, %rsi # to in rsi;
# 0 "" 2
#NO_APP
	movl	$0, %eax
#APP
# 84 "4-2.c" 1
	movq %rax, %rax # result in rax;
# 0 "" 2
# 87 "4-2.c" 1
	.L2:
addq %rdi, %rax;
addq $1, %rdi;
cmpq %rsi, %rdi;
jle .L2;

# 0 "" 2
# 134 "4-2.c" 1
	movq %rax, %rax  # result in rax;
# 0 "" 2
#NO_APP
	ret
	.cfi_endproc
.LFE22:
	.size	sum, .-sum
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"==Executing test 1=="
.LC1:
	.string	"Test 1 output: %ld\n"
.LC2:
	.string	"=========================="
.LC3:
	.string	"==Executing test 2=="
.LC4:
	.string	"Test 2 output: %ld\n"
.LC5:
	.string	"==Executing test 3=="
.LC6:
	.string	"Test 3 output: %ld\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB23:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	leaq	.LC0(%rip), %rdi
	call	puts@PLT
	movl	$6, %esi
	movl	$1, %edi
	call	sum
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC2(%rip), %rdi
	call	puts@PLT
	leaq	.LC3(%rip), %rdi
	call	puts@PLT
	movl	$5, %esi
	movl	$3, %edi
	call	sum
	movq	%rax, %rsi
	leaq	.LC4(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC2(%rip), %rdi
	call	puts@PLT
	leaq	.LC5(%rip), %rdi
	call	puts@PLT
	movl	$3, %esi
	movl	$5, %edi
	call	sum
	movq	%rax, %rsi
	leaq	.LC6(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC2(%rip), %rdi
	call	puts@PLT
	movl	$0, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE23:
	.size	main, .-main
	.ident	"GCC: (Arch Linux 9.3.0-1) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
