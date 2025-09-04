bits 64

extern __errno_location

section .data
section	.text

%macro IO_WRAPPER 2
    global %1
    %1:
        push	rbp
        mov		rbp, rsp

        mov     rax, %2
        syscall
        or      rax, rax
        jl      .fail
        jmp     .done

        .fail:
            mov     rdx, rax
            neg     rdx
            call    __errno_location wrt ..plt
            mov     [rax], rdx
            mov     rax, -1
        
        .done:
            pop     rbp
            ret
%endmacro

IO_WRAPPER ft_read, 0
IO_WRAPPER ft_write, 1
