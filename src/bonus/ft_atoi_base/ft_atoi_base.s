bits 64

section .data
section	.text

extern	ft_strlen

global	ft_atoi_base

ft_atoi_base:
	push	rbp
	mov		rbp, rsp

	; rdi = str ; rsi = base
	; rax = result ; rbx = sign ; rcx = i ; rdx = len

	call	check_base_error
	cmp		rax, 2
	jl		.error
	mov		rdx, rax
	xor		rcx, rcx
	call	get_sign
	mov		rbx, rax
	xor		rax, rax

	.loop:
		push	rax
		call	char_in_base
		mov		r9, rax
		pop		rax
		cmp		r9, -1
		je		.done
		imul	rax, rdx
		add		rax, r9
		inc		rcx
		jmp		.loop

	.error:
		xor		rax, rax
		jmp		.done

	.done:
		imul	rax, rbx
		pop		rbp
		ret

check_base_error:
	xor		rax, rax

	or		rsi, rsi
	je		.error

	.loop:
		cmp		BYTE [rsi + rax], 0
		je		.done
		xor		rbx, rbx

		.loop_nested:
			cmp		BYTE [rsi + rbx], 0
			je		.check_illegal_char
			cmp		rax, rbx
			je		.continue_loop_nested
			mov		cl, [rsi + rax]
			cmp		cl, [rsi + rbx]
			je		.error

			.continue_loop_nested:
				inc		rbx
				jmp		.loop_nested

		.check_illegal_char:
			cmp		BYTE [rsi + rax], 45
			je		.error
			cmp 	BYTE [rsi + rax], 43
			je 		.error
			cmp 	BYTE [rsi + rax], 32
			je 		.error
			cmp 	BYTE [rsi + rax], 13
			je 		.error
			cmp 	BYTE [rsi + rax], 12
			je 		.error
			cmp 	BYTE [rsi + rax], 11
			je 		.error
			cmp 	BYTE [rsi + rax], 10
			je 		.error
			cmp		BYTE [rsi + rax], 9
			je		.error

		inc rax
		jmp .loop

	.error:
		xor rax, rax
		ret

	.done:
		ret


get_sign:
	mov		rbx, 1

	.skip_spaces:
		cmp		BYTE [rdi + rcx], 32
		je		.continue_skip_spaces
		cmp 	BYTE [rdi + rcx], 13
		je 		.continue_skip_spaces
		cmp 	BYTE [rdi + rcx], 12
		je 		.continue_skip_spaces
		cmp 	BYTE [rdi + rcx], 11
		je 		.continue_skip_spaces
		cmp 	BYTE [rdi + rcx], 10
		je 		.continue_skip_spaces
		cmp		BYTE [rdi + rcx], 9
		je		.continue_skip_spaces
		jmp		.mult_sign

		.continue_skip_spaces:
			inc		rcx
			jmp		.skip_spaces

	.mult_sign:
		cmp		BYTE [rdi + rcx], 45
		je		.neg_sign
		cmp		BYTE [rdi + rcx], 43
		je		.pos_sign
		jmp		.done

		.neg_sign:
			neg		rbx
			inc		rcx
			jmp		.mult_sign

		.pos_sign:
			inc		rcx
			jmp		.mult_sign

	.done:
		mov		rax, rbx
		ret

char_in_base:
	xor		rax, rax
	xor		r9, r9

	.loop:
		mov		r8b, [rsi + r9]
		or		r8b, r8b
		je		.not_found
		cmp		BYTE [rdi + rcx], r8b
		je		.found
		inc		r9
		jmp		.loop

	.found:
		mov		rax, r9
		ret

	.not_found:
		mov		rax, -1
		ret