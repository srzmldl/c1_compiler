	.file	"calcSum.c"
	.section	.rodata
.LC0:
	.string	"%d"
.LC1:
	.string	" + %d"
.LC2:
	.string	"= %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movl	$10, -52(%rbp)
	movl	$10, -48(%rbp)
	movl	$7, -44(%rbp)
	movl	$5, -40(%rbp)
	movl	$100, -36(%rbp)
	movl	$1, -32(%rbp)
	movl	$7, -28(%rbp)
	movl	$67, -24(%rbp)
	movl	$4, -20(%rbp)
	movl	$99, -16(%rbp)
	movl	$6, -12(%rbp)
	movl	$0, -60(%rbp)
	movl	$0, -56(%rbp)
	jmp	.L2
.L3:
	movl	-60(%rbp), %eax
	cltq
	movl	-48(%rbp,%rax,4), %eax
	addl	%eax, -56(%rbp)
	addl	$1, -60(%rbp)
.L2:
	movl	-60(%rbp), %eax
	cmpl	-52(%rbp), %eax
	jl	.L3
	movl	-48(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$0, -60(%rbp)
	jmp	.L4
.L5:
	movl	-60(%rbp), %eax
	cltq
	movl	-48(%rbp,%rax,4), %eax
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	addl	$1, -60(%rbp)
.L4:
	movl	-60(%rbp), %eax
	cmpl	-52(%rbp), %eax
	jl	.L5
	movl	-56(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
