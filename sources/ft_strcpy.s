bits 64

section .data
section	.text

global	ft_strcpy

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

section .note.GNU-stack noalloc noexec nowrite progbits
