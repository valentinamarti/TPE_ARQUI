GLOBAL do_sys_write
GLOBAL do_sys_read
GLOBAL do_sys_clear
GLOBAL do_sys_get_time
GLOBAL do_sys_get_registers
GLOBAL do_sys_set_font_size
GLOBAL do_sys_draw_rectangle
GLOBAL do_sys_play_sound
GLOBAL do_sys_sleep
GLOBAL do_sys_exit
GLOBAL do_sys_new_line
GLOBAL do_sys_clear_sb
GLOBAL do_sys_call_div
GLOBAL division

section .text

do_sys_write:   ; do_sys_write(char* buffer, int longitud, int fd, color_t color, int container_id);
 	push rbp
    mov rbp, rsp

	; rbx
	; r12 - r15

	push rdi
	push rsi
	push rdx
	push rcx
    push r8
	push r9

	mov r9, r8 			; r9 -> container_id
    mov r8, rcx         ; r8 -> color
	mov rcx, rdx        ; rcx -> filedescriptor
	mov rdx, rsi        ; rdx -> longitud
	mov rsi, rdi        ; rsi -> buffer
	mov rdi, 0
	int 80h

	pop r9
    pop r8
	pop rcx
	pop rdx
	pop rsi
	pop rdi

    mov rsp, rbp
    pop rbp
    ret

do_sys_read:            ; do_sys_read(char* buffer, int longitud, int fd);
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

do_sys_clear:		 ; do_sys_clear(int container_id)
	push rbp
    mov rbp, rsp

	push rdi
	push rsi

	mov rsi, rdi 		; rsi -> container_id
	mov rdi, 2
	int 80h

	pop rsi
	pop rdi

    mov rsp, rbp
    pop rbp
    ret

do_sys_get_time:		;do_sys_get_time(int* hrs, int* min, int* sec)
	push rbp
    mov rbp, rsp

	push rdi
	push rsi
	push rdx
	push rcx

	mov rcx, rdx        ; rcx -> puntero a sec
	mov rdx, rsi        ; rdx -> puntero a min
	mov rsi, rdi        ; rsi -> puntero a hrs
	mov rdi, 3
	int 80h

	pop rcx
	pop rdx
	pop rsi
	pop rdi

    mov rsp, rbp
    pop rbp
    ret    

do_sys_get_registers:
	push rbp
    mov rbp, rsp

	push rdi
	push rsi

	mov rsi, rdi        ; rsi -> puntero al vector de registros
	mov rdi, 4
	int 80h

	pop rsi
	pop rdi

    mov rsp, rbp
    pop rbp
    ret    



do_sys_set_font_size:		; do_sys_set_font_size(int size)
	push rbp
    mov rbp, rsp

	push rdi
	push rsi
	push rdx

	mov rdx, rsi 		; rdx -> container_id
	mov rsi, rdi        ; rsi -> size a aumentar
	mov rdi, 5
	int 80h

	pop rdx
	pop rsi
	pop rdi

    mov rsp, rbp
    pop rbp
    ret    


do_sys_draw_rectangle:     ; sys_draw_rectangle(int posx, int posy, int sizex, int sizey, color_t color, int container_id)
 	push rbp
    mov rbp, rsp

	push rdi
	push rsi
	push rdx
	push rcx
	push r8 
	push r9

	push r9				; container_id
	mov r9, rdx			; r9 -> color
	mov r8, rcx			; r8 -> sizey
	mov rcx, rdx        ; rcx -> sizex
	mov rdx, rsi        ; rdx -> posy
	mov rsi, rdi        ; rsi -> posx
	mov rdi, 6
	int 80h
	pop r9 
	
	pop r9 
	pop r8
	pop rcx
	pop rdx
	pop rsi
	pop rdi

    mov rsp, rbp
    pop rbp
    ret  

do_sys_play_sound:		; lo hice asi generico, pero de momento no rcibe si devuelve nada
 	push rbp
    mov rbp, rsp

	push rdi

	mov rdi, 7
	int 80h
	
	pop rdi

    mov rsp, rbp
    pop rbp
    ret  
do_sys_sleep:			; do_sys_sleep(int seconds)
 	push rbp
    mov rbp, rsp

	push rdi
	push rsi

	mov rsi, rdi        ; rsi -> seconds
	mov rdi, 8
	int 80h
	
	pop rsi
	pop rdi

    mov rsp, rbp
    pop rbp
    ret  
do_sys_exit:			; do_sys_exit(int container_id)
 	push rbp
    mov rbp, rsp

	push rdi
	push rsi

	mov rsi, rdi        ; rsi -> container_id
	mov rdi, 9
	int 80h
	
	pop rsi
	pop rdi

    mov rsp, rbp
    pop rbp
    ret  

do_sys_new_line:		; do_sys_new_line(int container_id)
	push rbp
    mov rbp, rsp

	push rdi
	push rsi

	mov rsi, rdi        ; rsi -> container_id
	mov rdi, 10
	int 80h
	
	pop rsi
	pop rdi

    mov rsp, rbp
    pop rbp
    ret

do_sys_clear_sb:		 ; do_sys_clear_sb(int container_id)
	push rbp
    mov rbp, rsp

	push rdi
	push rsi

	mov rsi, rdi 		; rsi -> container_id
	mov rdi, 11
	int 80h

	pop rsi
	pop rdi

    mov rsp, rbp
    pop rbp
    ret

do_sys_call_div:		 ;  do_sys_call_div(int dividendo, int divisor)
	push rbp
    mov rbp, rsp

	push rdi
	push rsi
	push rdx

	mov rdx, rsi 		; rdx -> divisor
	mov rsi, rdi 		; rsi -> dividendo
	mov rdi, 11
	int 80h

	pop rdx
	pop rsi
	pop rdi

    mov rsp, rbp
    pop rbp
    ret

division:
	mov rdi, 0
	mov rax, 1
	mov rdx, 0

	div rdi
