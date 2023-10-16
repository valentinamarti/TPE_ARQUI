GLOBAL cpuVendor
GLOBAL getKey
GLOBAL getKeyPressed

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

getKey:
    enter 0,0
.wait:
    xor rax,rax

    in al, 0x64
    test al, 1
    jz .wait

    in al, 0x60

    leave
    ret

getKeyPressed:
    push rbp
    mov rbp, rsp

    xor rax, rax
    in al, 60h

    mov rsp, rbp
    pop rbp
    ret





