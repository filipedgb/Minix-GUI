.globl _keyboard_int_handler_ASM
_keyboard_int_handler_ASM:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_kbc_output
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	cmpl	$129, %eax
	jne	L8
	movl	$1, %eax
	jmp	L9
L8:
	movl	$0, %eax
L9:
	leave
	ret
	.balign 4
LC0:
	.ascii "Escape break code: %2x.\12Terminating...\12\0"
LC1:
	.ascii "Function in assembly | Break code: %2x\12\0"
LC2:
	.ascii "Function in assembly | Make code: %2x\12\0"
