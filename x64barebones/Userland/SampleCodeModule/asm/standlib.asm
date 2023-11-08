
GLOBAL smalloc
GLOBAL sfree
section .text

;=========================================================
;   Argumentos: 0
;   Devuelve: Devuelve un puntero a ese espacio de memoria
;=========================================================


smalloc:
    push rbp
	mov rbp, rsp

    push rbx
    push rcx
    push rdx
    mov rbx, chunk_size_100
    mov rcx, cant_chunks_100
    mov rdx,chunk100


.loop: cmp rcx, 0
    je .error
    mov al, [rdx]
    cmp al, 0
    je .fin
    dec rcx
    add rdx, rbx
    jmp .loop



.fin:
    mov rax, rdx
    mov BYTE[rdx], 1
    inc rax             ; Aumento el puntero para no pisar la flag

.ret:pop rdx
    pop rcx
    pop rbx
    mov rsp, rbp
    pop rbp
    ret

.error:
    mov rax, -1
    jmp .ret


;=========================================================
;   Argumentos: Puntero a la zona a liberar
;   Devuelve: Devuelve un puntero a ese espacio de memoria
;=========================================================


sfree:
    push rbp
	mov rbp, rsp

    dec rdi
    mov BYTE[rdi], 0
    inc rdi
    mov rsp, rbp
    pop rbp
    ret


section .data

chunk_size_100 dq 100
cant_chunks_100 dq 150

section .bss

chunk100 resb 15000
; Puede guardar 100 chunks de 100 bytes