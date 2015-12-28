	.text
	.file	"a.ll"
	.globl	_Z2ffv
	.align	16, 0x90
	.type	_Z2ffv,@function
_Z2ffv:                                 # @_Z2ffv
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp0:
	.cfi_def_cfa_offset 16
.Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp2:
	.cfi_def_cfa_register %rbp
	movl	$2, -4(%rbp)
	popq	%rbp
	retq
.Ltmp3:
	.size	_Z2ffv, .Ltmp3-_Z2ffv
	.cfi_endproc

	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp4:
	.cfi_def_cfa_offset 16
.Ltmp5:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp6:
	.cfi_def_cfa_register %rbp
	movl	$1, -4(%rbp)
	movl	$2, -8(%rbp)
	movl	$3, -12(%rbp)
	xorl	%eax, %eax
	popq	%rbp
	retq
.Ltmp7:
	.size	main, .Ltmp7-main
	.cfi_endproc


	.ident	"clang version 3.6.0 (tags/RELEASE_360/final 254901)"
	.section	".note.GNU-stack","",@progbits
