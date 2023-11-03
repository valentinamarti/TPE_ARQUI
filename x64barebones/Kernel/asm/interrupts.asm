
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
GLOBAL getRegisters

EXTERN irqDispatcher
EXTERN exceptionDispatcher
EXTERN syscallsDispatcher
EXTERN getStackBase

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

	mov rdi, %1 ; pasaje de parametro
	call irqDispatcher
	
	cmp rax, 1		; comparo el calor que me devuelve irqDispatcher, que le devolvio keyboardHandler 
					; que me indica si tengo que capturar los registros o no 
	jne .continue
	mov [registers], rax
    mov [registers + 8], rbx
    mov [registers + 16], rcx
    mov [registers + 24], rdx
    mov [registers + 32], rsi
	mov [registers + 40], rdi
    mov [registers + 48], rbp
    mov [registers + 64], r8
    mov [registers + 72], r9
    mov [registers + 80], r10
    mov [registers + 88], r11
    mov [registers + 96], r12
    mov [registers + 104], r13
    mov [registers + 112], r14
    mov [registers + 120], r15

	mov rax, rsp
	mov [registers+ 56], rax  		; rsp
	mov rax, [rsp]
	mov [registers + 128], rax 		; rip

.continue:
	mov al, 20h						; signal pic EOI (End of Interrupt)
	out 20h, al

	popState
	iretq

%endmacro

%macro exceptionHandler 1

	mov [registers], rax
    mov [registers + 8], rbx
    mov [registers + 16], rcx
    mov [registers + 24], rdx
    mov [registers + 32], rsi
	mov [registers + 40], rdi
    mov [registers + 48], rbp
    mov [registers + 64], r8
    mov [registers + 72], r9
    mov [registers + 80], r10
    mov [registers + 88], r11
    mov [registers + 96], r12
    mov [registers + 104], r13
    mov [registers + 112], r14
    mov [registers + 120], r15

	mov rax, rsp
	mov [registers+ 56], rax  		; rsp
	mov rax, [rsp]
	mov [registers + 128], rax 		; rip
	
	mov rdi, %1 					; pasaje de parametro
	mov rsi, registers				; le paso el array con los registros capturados como parametro
	call exceptionDispatcher

    mov qword[rsp], userland		; vuelvo a la direc segura 
    call getStackBase
	mov qword[rsp+24], rax

	iretq
%endmacro

getRegisters:
	mov rax, registers
	ret

_int80Handler:	; en rdi el mode, luego en el resto de los registros los parametros usuales de cada syscall
	pushState
	call syscallsDispatcher
	popState
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
	registers resq 17	;registrs when there is an exception