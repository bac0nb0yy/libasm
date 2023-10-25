extern	malloc
extern	__errno_location
extern	ft_strlen
extern	ft_strcpy
global	ft_strdup
section	.text

ft_strdup:
	push    rbp
	mov     rbp, rsp

	call    ft_strlen
	inc 	rax

	mov		rbx, rdi
	mov 	rdi, rax
	call	malloc
	or 		rax, rax
	jle		.error_handler

	mov		rdi, rax
	mov		rsi, rbx
	call	ft_strcpy
	jmp		.done

	.error_handler:
		call	__errno_location
		mov		rbx, 12			;ENOMEM is the only error that can occurs.
		mov		[rax], rbx
		xor		rax, rax
		jmp		.done

	.done:
		pop		rbp
		ret