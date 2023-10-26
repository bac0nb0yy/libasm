bits 64

section .data
section	.text

global	ft_strcmp

ft_strcmp:
	push	rbp
	mov		rbp, rsp

	xor		rax, rax
	xor		rbx, rbx
	xor		rcx, rcx

	.loop:
		mov		al, [rdi + rcx]
		mov		bl, [rsi + rcx]
		cmp		al, bl
		jne		.done
		or		al, al
		je		.done
		inc		rcx
		jmp		.loop

	.done:
		sub		eax, ebx
		pop		rbp
		ret