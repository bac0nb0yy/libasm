bits 64

global ft_strlen

section .data
section .text

ft_strlen:
    xor     rax, rax

    .loop:
		cmp     byte [rdi + rax], 0
		je      .done
		inc     rax
		jmp     .loop

	.done:
		ret
