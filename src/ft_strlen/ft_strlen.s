bits 64

section .data
section	.text

global	ft_strlen

ft_strlen:
	push	rbp
	mov		rbp, rsp

	xor		rax, rax

	.loop:
		cmp		BYTE [rdi + rax], 0
		je		.done
		inc		rax
		jmp		.loop

	.done:
		pop		rbp
		ret