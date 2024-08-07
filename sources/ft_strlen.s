bits 64

section .data

section .text

global ft_strlen

ft_strlen:
    push    rbp
    mov     rbp, rsp

    mov     rax, rdi
    vpxor   ymm0, ymm0, ymm0

    .loop:
        vmovdqu		ymm1, [rax]
        vpcmpeqb	ymm2, ymm1, ymm0
        vpmovmskb	edx, ymm2
        test		edx, edx
        jnz			.found_zero
        add			rax, 32
        jmp			.loop

    .found_zero:
        bsf		ecx, edx
        add		rax, rcx

    sub		rax, rdi
    pop		rbp
    vzeroupper
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
