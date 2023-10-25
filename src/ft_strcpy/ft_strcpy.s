bits 64

section .data
section	.text

global	ft_strcpy

ft_strcpy:
    push	rbp
    mov		rbp, rsp

	xor		rbx, rbx

	.loop:
		mov		al, [rsi + rbx]
		mov		[rdi + rbx], al
		inc		rbx
		or		al, al
		je		.done
		jmp		.loop

	.done:
		pop		rbp
		mov		rax, rdi
		ret