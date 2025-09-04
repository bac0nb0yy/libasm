bits 64

global	ft_strcmp

section .data
section	.text

ft_strcmp:
	push	rbp
	mov		rbp, rsp

	xor		eax, eax
	xor		r8d, r8d
	xor		rcx, rcx

	.loop:
		mov		al, [rdi + rcx]
		mov		r8b, [rsi + rcx]
		cmp		al, r8b
		jne		.done
		or		al, al
		je		.done
		inc		rcx
		jmp		.loop

	.done:
		sub		eax, r8d
		pop		rbp
		ret
