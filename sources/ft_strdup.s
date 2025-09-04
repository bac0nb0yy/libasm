bits 64

global	ft_strdup
extern	malloc, __errno_location, ft_strlen, ft_strcpy

section .data
section	.text

ft_strdup:
	push    rbp
	mov     rbp, rsp

	xor		rax, rax

	call    ft_strlen
	inc 	rax

	mov		r12, rdi
	mov 	rdi, rax
	call	malloc wrt ..plt
	or 		rax, rax
	je		.done

	mov		rdi, rax
	mov		rsi, r12
	call	ft_strcpy
	jmp		.done

	.done:
		pop		rbp
		ret
