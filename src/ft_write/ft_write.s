extern	__errno_location
global	ft_write
section	.text

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
		mov		rbx, rax
		pop		rax
		neg		rax
		mov		[rbx], rax
		mov		rax, -1
		jmp		.done

	.done:
		pop		rbp
		ret