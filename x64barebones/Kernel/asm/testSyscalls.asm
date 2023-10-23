GLOBAL do_sys_write
section .text

do_sys_write:
mov rdi, 0
int 80h
ret 