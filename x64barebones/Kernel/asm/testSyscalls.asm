do_sys_write:   ; do_sys_write(char* buffer, int longitud, int fd, color_t color);
 push rbp
    mov rbp, rsp

	push rdi
	push rsi
	push rdx
	push rcx
    push r8

    mov r8, rcx         ; color
	mov rcx, rdx        ; rcx -> filedescriptor
	mov rdx, rsi        ; rdx -> longitud
	mov rsi, rdi        ; rsi -> buffer
	mov rdi, 0
	int 80h

    pop r8
	pop rcx
	pop rdx
	pop rsi
	pop rdi

    mov rsp, rbp
    pop rbp
    ret

do_sys_read:       ; do_sys_read(char* buffer, int longitud, int fd);
 push rbp
    mov rbp, rsp

	push rdi
	push rsi
	push rdx
	push rcx

	mov rcx, rdx        ; rcx -> filedescriptor
	mov rdx, rsi        ; rdx -> longitud
	mov rsi, rdi        ; rsi -> buffer (en donde devuelvo lo leido)
	mov rdi, 1
	int 80h

	pop rcx
	pop rdx
	pop rsi
	pop rdi

    mov rsp, rbp
    pop rbp
    ret    