bits 64

section .data
section	.text

extern __errno_location

%macro IO_WRAPPER 2
    global %1
    %1:
        mov rax, %2
        syscall
        or rax, rax
        je .fail
        ret
        .fail:
            mov rdx, rax
            neg rdx
            call __errno_location wrt ..plt
            mov [rax], rdx
            mov rax, -1
            ret
%endmacro

IO_WRAPPER ft_read, 0
IO_WRAPPER ft_write, 1