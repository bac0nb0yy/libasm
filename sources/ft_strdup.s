bits 64

section .data
section	.text

extern	malloc
extern	__errno_location
extern	ft_strlen
extern	ft_strcpy

global	ft_strdup

ft_strdup:
	push    rbp
	mov     rbp, rsp

	call    ft_strlen
	inc 	rax

	mov		r12, rdi
	mov 	rdi, rax
	call	malloc
	or 		rax, rax
	je		.error_handler

	mov		rdi, rax
	mov		rsi, r12
	call	ft_strcpy
	jmp		.done

	.error_handler:
		; call	__errno_location
		; mov		BYTE [rax], 12	;ENOMEM is the only error that can occurs.
		xor		rax, rax
		jmp		.done

	.done:
		pop		rbp
		ret