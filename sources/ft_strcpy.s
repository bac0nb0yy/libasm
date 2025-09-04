bits 64

global	ft_strcpy

section .data
section	.text

ft_strcpy:
    push	rbp
    mov		rbp, rsp

	xor		rcx, rcx

	.loop:
		mov		al, [rsi + rcx]
		mov		[rdi + rcx], al
		inc		rcx
		or		al, al
		je		.done
		jmp		.loop

	.done:
		mov		rax, rdi
		pop		rbp
		ret
