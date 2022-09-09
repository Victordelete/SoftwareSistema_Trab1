section .text

global _start

_start:

    push VAR_0
    push VAR_0
    call s_input ; INPUT STRING
    mov     ecx,    MsgLidos1 ; Inicio msg quantidade bytes lidos
    mov     edx,    LenMsgLidos1
    mov     ebx,    1
    int     0x80
    call impQtdBytes; funcao imprimi valor que esta como resultado na pilha
    mov     ecx,    MsgLidos2 ;
    mov     edx,    LenMsgLidos2
    mov     ebx,    1
    int     0x80
    add     ebp, 4 ; Desempilho o resultado

    push VAR_1
    push VAR_1
    call s_output ; INPUT STRING
    mov     ecx, MsgLidos1 ; Inicio msg quantidade bytes escritos
    mov     edx, LenMsgLidos1
    mov     ebx, 1
    int     0x80
    call impQtdBytes; funcao imprimi valor que esta como resultado na pilha
    mov     ecx, MsgLidos2 ;
    mov     edx, LenMsgLidos2
    mov     ebx, 1
    int     0x80
    add     ebp, 4 ; Desempilho o resultado

    push VAR_13
    call input ; input
    mov     ecx,    MsgLidos1 ; Inicio msg quantidade bytes lidos
    mov     edx,    LenMsgLidos1
    mov     ebx,    1
    int     0x80
    call impQtdBytes; funcao imprimi valor que esta como resultado na pilha
    mov     ecx,    MsgLidos2 ;
    mov     edx,    LenMsgLidos2
    mov     ebx,    1
    int     0x80
    add     ebp, 4 ; Desempilho o resultado

    push VAR_14
    call input ; input
    mov     ecx,    MsgLidos1 ; Inicio msg quantidade bytes lidos
    mov     edx,    LenMsgLidos1
    mov     ebx,    1
    int     0x80
    call impQtdBytes; funcao imprimi valor que esta como resultado na pilha
    mov     ecx,    MsgLidos2 ;
    mov     edx,    LenMsgLidos2
    mov     ebx,    1
    int     0x80
    add     ebp, 4 ; Desempilho o resultado

    mov edx, VAR_13 ; LOAD

    add edx, VAR_14 ; ADD

    mov VAR_15, edx ;STORE

    push VAR_15
    call output ; OUTPUT
    mov     ecx,    MsgLidos1 ; Inicio msg quantidade bytes lidos
    mov     edx,    LenMsgLidos1
    mov     ebx,    1
    int     0x80
    call impQtdBytes; funcao imprimi valor que esta como resultado na pilha
    mov     ecx,    MsgLidos2 ;
    mov     edx,    LenMsgLidos2
    mov     ebx,    1
    int     0x80
    add     ebp, 4 ; Desempilho o resultado


    mov eax, 1
    int 0x80 ; STOP

section .data ; CONST
     VAR_22 db '2'
     VAR_23 db '17'

     MsgLidos1 db "Foram lidos/escritos "
     lenMsgLidos1 equ $ - MsgLidos1
     MsgLidos2 db " bytes" 
     lenMsgLidos2 equ $ - MsgLidos2

section .bss ; SPACE
     VAR_19 resb 1
     VAR_20 resb 1
     VAR_21 resb 1
