bits 64

global	ft_strdup
extern	malloc, __errno_location, ft_strlen, ft_strcpy

section .data
section	.text

ft_strdup:
	push    rbp
	mov     rbp, rsp

	sub     rsp, 8
	push	rdi

	call    ft_strlen
	inc 	rax

	mov 	rdi, rax
	call	malloc wrt ..plt
	pop		rsi
	or 		rax, rax
	je		.done

	mov		rdi, rax
	call	ft_strcpy
	jmp		.done

	.done:
		add     rsp, 8
		pop		rbp
		ret
