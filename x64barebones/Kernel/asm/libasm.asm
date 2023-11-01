GLOBAL cpuVendor
GLOBAL getKey
GLOBAL getKeyPressed
GLOBAL getSeconds
GLOBAL getMinutes 
GLOBAL getHours
GLOBAL getDays
GLOBAL getMonth
GLOBAL getYear
GLOBAL cpuGetTime
GLOBAL hlt
EXTERN getStackBase

section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

;--------------------------------------------
; Esta me parece que no la vamos a usar
;--------------------------------------------
; getKey:
;     enter 0,0
; .wait:
;     xor rax,rax

;     in al, 0x64
;     test al, 1
;     jz .wait

;     in al, 0x60

;     leave
;     ret

getKeyPressed:
    push rbp
    mov rbp, rsp

    xor rax, rax
    in al, 60h

    mov rsp, rbp
    pop rbp
    ret

getSeconds:
    push rbp
    mov rbp, rsp

    xor rax, rax
    mov al, 0
    out 70h, al
    in al, 71h
   
    mov rsp, rbp
    pop rbp
    ret

getMinutes:                  
    push rbp
    mov rbp, rsp

    xor rax, rax
    mov al, 2
    out 70h, al
    in al, 71h
   
    mov rsp, rbp
    pop rbp
    ret

getHours:                  
    push rbp
    mov rbp, rsp

    xor rax, rax
    mov al, 4
    out 70h, al
    in al, 71h
   
    mov rsp, rbp
    pop rbp
    ret

hlt:
	sti
	hlt
	ret


section .data 
section .bss







