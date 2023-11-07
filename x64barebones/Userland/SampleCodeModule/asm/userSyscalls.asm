GLOBAL do_sys_write
GLOBAL do_sys_read
GLOBAL do_sys_clear
GLOBAL do_sys_get_time
GLOBAL do_sys_get_registers
GLOBAL do_sys_set_font_size
GLOBAL do_sys_draw_rectangle
GLOBAL do_sys_play_beep
GLOBAL do_sys_sleep
GLOBAL do_sys_exit_container
GLOBAL do_sys_new_line
GLOBAL do_sys_clear_sb
GLOBAL division
GLOBAL wrong_opcode
GLOBAL do_sys_new_container
GLOBAL do_sys_set_background
GLOBAL do_sys_set_border

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
	mov rdx, rsi        ; rdx -> longitudz
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

	mov rsi, rdi        ; rsi -> puntero a array registers
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
	mov r9, r8			; r9 -> color
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

do_sys_play_beep:		; do_sys_play_beep(int frecuency, int millisec);
 	push rbp
    mov rbp, rsp

	push rdi

	mov rdx, rsi        ; rdx -> millisec
	mov rsi, rdi        ; rsi -> frecuency
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
do_sys_exit_container:			; do_sys_exit_container(int container_id)
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

division:
	mov rdi, 0
	mov rax, 7
	mov rdx, 0

	div rdi

wrong_opcode:
	mov cr6, rax

do_sys_new_container: ; sys_new_container(uint8_t * name, uint16_t X0, uint16_t Y0,uint16_t width, uint16_t height);
	push rbp
    mov rbp, rsp

	push rdi
	push rsi
	push rdx
	push rcx
	push r8
	push r9

	push r9				; Push -> &container_id
	mov r9, r8			; r9 -> height
	mov r8, rcx			; r8 -> width
	mov rcx, rdx        ; rcx -> Y0
	mov rdx, rsi        ; rdx -> X0
	mov rsi, rdi        ; rsi -> name
	mov rdi, 12
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


do_sys_set_background:		 ; do_sys_set_background(color_t color, int container_id)
	push rbp
    mov rbp, rsp

	push rdi
	push rsi

	mov rdx, rsi        ; rdx -> container_id
	mov rsi, rdi        ; rsi -> color
	mov rdi, 13
	int 80h

	pop rsi
	pop rdi

    mov rsp, rbp
    pop rbp
    ret

do_sys_set_border:		 ; do_sys_set_border(color_t color, int container_id)
	push rbp
    mov rbp, rsp

	push rdi
	push rsi

	mov rdx, rsi        ; rdx -> container_id
	mov rsi, rdi        ; rsi -> color
	mov rdi, 14
	int 80h

	pop rsi
	pop rdi

    mov rsp, rbp
    pop rbp
    ret


do_sys_was_redrawed:		 ; do_sys_was_redrawed(int container_id)
	push rbp
    mov rbp, rsp

	push rdi
	push rsi

	mov rsi, rdi        ; rsi -> container_id
	mov rdi, 14
	int 80h

	pop rsi
	pop rdi

    mov rsp, rbp
    pop rbp
    ret





