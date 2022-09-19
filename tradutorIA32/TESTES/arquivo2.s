section .text

global _start

_start:

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
     VAR_9 db '1'
     VAR_10 db '3'
     VAR_12 db '2'
     VAR_13 db '17'

     MsgLidos1 db "Foram lidos/escritos "
     lenMsgLidos1 equ $ - MsgLidos1
     MsgLidos2 db " bytes" 
     lenMsgLidos2 equ $ - MsgLidos2

section .bss ; SPACE
     VAR_11 resb 1
