bits 64

section .data
section	.text

extern	malloc
extern	__errno_location

global	ft_list_push_front

ft_list_push_front:
	push	rbp
	mov		rbp, rsp

	or		rdi, rdi
	je		.done
	cmp		QWORD [rdi], 0
	je		.no_head

	call	create_node
	or		rax, rax
	je		.done
	mov		rdx, [rdi]
	mov		QWORD [rax + 8], rdx
	mov		[rdi], rax
	jmp		.done

	.no_head:
		call	create_node
		or		rax, rax
		je		.done
		mov		[rdi], rax
		jmp		.done

	.done:
		pop		rbp
		ret

create_node:
	push	rdi
	push	rsi
	mov		rdi, 16
	call	malloc
	pop		rsi
	pop		rdi
	or 		rax, rax
	je		.error_handler

	mov		QWORD [rax], rsi
	mov		QWORD [rax + 8], 0
	jmp		.done

	.error_handler:
		call	__errno_location
		mov		BYTE [rax], 12	;ENOMEM is the only error that can occurs.
		xor		rax, rax
		ret

	.done:
		ret