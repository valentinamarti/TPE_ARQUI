GLOBAL getSeconds
GLOBAL getMinutes 
GLOBAL getHours
GLOBAL getDays
GLOBAL getMonth
GLOBAL getYear

section .text 

getSeconds:
    push rbp
    mov rbp, rsp

    mov al, 0
    out 70h, al
    in ax, 71h
   
    mov rsp, rbp
    pop rbp
    ret

getMinutes:                  
    push rbp
    mov rbp, rsp

    mov al, 2
    out 70h, al
    in ax, 71h
   
    mov rsp, rbp
    pop rbp
    ret

getHours:                  
    push rbp
    mov rbp, rsp

    mov al, 4
    out 70h, al
    in ax, 71h
   
    mov rsp, rbp
    pop rbp
    ret


getDays:           
    push rbp
    mov rbp, rsp

    mov al, 6
    out 70h, al
    in ax, 71h
   
    mov rsp, rbp
    pop rbp
    ret

getMonth:          
    push rbp
    mov rbp, rsp

    mov al, 8
    out 70h, al
    in ax, 71h
   
    mov rsp, rbp
    pop rbp
    ret


getYear:      
    push rbp
    mov rbp, rsp

    mov al, 9
    out 70h, al
    in ax, 71h
   
    mov rsp, rbp
    pop rbp
    ret

section .data 
section .bss