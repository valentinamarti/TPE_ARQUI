
GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler
GLOBAL _int80Handler:
GLOBAL _exception0Handler
GLOBAL _exception6Handler

EXTERN irqDispatcher
EXTERN exceptionDispatcher
EXTERN syscallsDispatcher
EXTERN getStackBase
EXTERN saveRegisters

SECTION .text

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

%macro irqHandlerMaster 1
	pushState

	mov [ripaux], rsp		; guarda el rip y el rsp antes de hacer nada
	push rax
	lea rax, [rsp + 4 * 8]
	mov [rspaux], rax
	pop rax

	mov [raxaux], rax		; guarda el rax y rdi antes de usarlos
	mov [rdiaux], rdi
	
	mov rdi, %1 ; pasaje de parametro
	call irqDispatcher
	
	cmp rax, 1		; compara el valor que me devuelve irqDispatcher, que le devolvio keyboardHandler 
					; que me indica si tengo que capturar los registros o no 
	jne .continue
	
	mov rax, [raxaux]
	mov rdi, [rdiaux]
	pushState

	mov rdx, rsp			; rdx -> stack
	mov rsi, [rspaux]		; rsi -> rsp
	mov rdi, [ripaux]		; rdi -> rip
	call saveRegisters
	
	popState

.continue:
	mov al, 20h						; signal pic EOI (End of Interrupt)
	out 20h, al

	popState
	iretq

%endmacro

%macro exceptionHandler 1

	mov [ripaux], rsp
	push rax
	lea rax, [rsp + 4 * 8]
	mov [rspaux], rax
	pop rax

	pushState

	mov rcx, rsp			; rcx -> stack
	mov rdx, [rspaux]		; rdx -> rsp
	mov rsi, [ripaux]		; rsi -> rip
	mov rdi, %1
	call exceptionDispatcher

	popState
    mov qword[rsp], userland		; vuelvo a la direc segura 
    call getStackBase
	mov qword[rsp+24], rax

	iretq
%endmacro


_int80Handler:	; en rdi el mode, luego en el resto de los registros los parametros usuales de cada syscall
	push rbp
	push rsp 
	push r12
	push r13
	push r15

	call syscallsDispatcher
	
	pop r15
	pop r13
	pop r12
	pop rsp 
	pop rbp
	iretq 


_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret


_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn


;8254 Timer (Timer Tick)
_irq00Handler:
	irqHandlerMaster 0

;Keyboard
_irq01Handler:
	irqHandlerMaster 1

;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
	irqHandlerMaster 4

;USB
_irq05Handler:
	irqHandlerMaster 5


;Zero Division Exception
_exception0Handler:
	exceptionHandler 0

;Wrong Opcode Exception
_exception6Handler:
	exceptionHandler 6


haltcpu:
	cli
	hlt
	ret



SECTION .data
userland equ 0x400000

SECTION .bss
	aux resq 1
	ripaux resb 8
	rspaux resb 8
	raxaux resb 8
	rdiaux resb 8
	registers resq 17