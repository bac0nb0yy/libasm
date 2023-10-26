bits 64

section .data
section	.text

extern	__errno_location

global	ft_write

ft_write:
	push	rbp
	mov		rbp, rsp

	mov		rax, 1
	syscall

	or		rax, rax
	jl		.error_handler
	jmp		.done

	.error_handler:
		push	rax
		call	__errno_location
		mov		rdx, rax
		pop		rax
		neg		rax
		mov		[rdx], rax
		mov		rax, -1
		jmp		.done

	.done:
		pop		rbp
		ret