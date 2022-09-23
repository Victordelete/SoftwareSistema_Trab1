section .text

global _start

;-------------------------------------------------------------------------------
;;;;;OUTPUT INICIO

output:
    push    ebp
    mov     ebp, esp ;salvando o contexto da pilha
    
    push    edx
    push    ecx
    push    ebx
    
    mov     [valorInput], dword 0   ;sera usado para o indice do output
    
    mov     eax, [ebp+8]
    xor     ecx, ecx ;; zero o meu contador
    mov     dword [valorOutput], eax ;carregando valor a ser representado
    cmp     eax, 0
    jge     output_loop ;se maior que zero inicio o ciclo se menor imprimo um menos
    
    mov     eax, [ebp+8]
    neg     eax
    mov     dword [valorOutput], eax ;carregando valor a ser representado caso seja negativo
    
    mov     edx, '-'
    mov     [temp], edx
    add     [valorInput], dword  1
    
    mov     ecx, temp
    mov     edx, 1
    mov     ebx, 1 
    mov     eax, 4 
    int     0x80
    
    xor     ecx, ecx ;; zero o meu contador

    output_loop: ; Loop principal da funcao OUTPUT
        xor     edx, edx          ; edx = 0
        mov     eax, dword [valorOutput]; valor para 
        mov     ebx, dword 10   ; divisor
        div     ebx             ;
        mov     dword [valorOutput], eax
        
        add     edx, '0'
        mov     [buffer+ecx], edx ; salvo o digito como char
        inc     ecx ; incremento contador
        
        mov     edx, dword[valorOutput]
        
        cmp     edx, dword 0
        jne     output_loop
        
        mov     [ind], ecx      ;seto o indice de saida
        sub     ecx, dword 1    ;corrigindo ultima soma excesso
        add     [valorInput], ecx
        
    output_saida: ; Loop secundario da funcao OUTPUT
        push    ecx
        
        mov     edx, [buffer+ecx]
        mov     [temp], edx
        
        mov     ecx, temp
        mov     edx, 1
        mov     ebx, 1 
        mov     eax, 4 
        int     0x80             ;imprimir resultado
        
        pop     ecx
        sub     ecx, dword 1
        cmp     ecx, dword -1
        jne     output_saida
    
    mov     eax, [valorInput]
    add     eax, 1
    
    pop     ebx
    pop     ecx
    pop     edx
    pop     ebp
    ret     4
;;;;;OUTPUT FINAL

;-------------------------------------------------------------------------------
;;;;;INICIO INPUT
input:
    push    ebp
    mov     ebp, esp ;salvando o contexto da pilha

    mov     [ind], dword 0
    mov     [valorInput], dword 0 ; zerando entradas iniciais
    mov     [valorOutput], dword 0; indice de saida
    mov     [buffer+4], dword 0   ;zerando indice 
    
    mov     ecx, buffer
    mov     edx, 1
    mov     ebx, 0
    mov     eax, 3
    int     0x80        ;Leio um numero
    
    cmp     [buffer], dword 45       ;comparo com menos '-'
    jne     input_loopIf            ;se nÃ£o negativo continuo 
    
    mov     [buffer+4], dword 1
    add     [valorOutput], dword 1  ; em caso negativo eu seto representa negativo e adiciono 1 ao indice
    
    input_loop:
        
        mov     ecx, buffer
        mov     edx, 1
        mov     ebx, 0
        mov     eax, 3
        int     0x80        ;Leio um numero
        input_loopIf:
        
        cmp     [buffer], dword 10
        je      inputFim        ; comparo com enter se true fim
        
        sub     [buffer], dword '0' ; transformo para nÃºmero
        
        mov     eax, [buffer]
        add     eax, [valorInput]   ;
        
        mov     ebx, dword 10       ;multiplico o parcial por 10
        mul     ebx
        
        mov     [valorInput], eax
        
        inc     dword [ind] ; atualizando indice
        
        jmp     input_loop
    
    inputFim:
        xor     edx, edx
        mov     eax, [valorInput]
        mov     ebx, dword 10
        div     ebx             ;corrijo o indice final dividindo por 10
        
        mov     [valorInput], eax   ;guardo o valor gerado
        
    signalHandle:
        cmp     [buffer+4], dword 1      ;registro de memoria usado como buffer de entrada e de saida
        jne     inputSaida
        mov     eax, [valorInput]
        neg     eax
        mov     [valorInput], eax
    
    inputSaida:
        mov     eax, [ind]
        add     eax, [valorOutput]      ;saldo o indice em eax
        mov     ebx, [valorInput]       ;salvo o valor lido em 
        
    pop     ebp
    ret     4
;;;;;SAIDA INPUT

;-------------------------------------------------------------------------------
;;;;;INICIO impQtdBytes
impQtdBytes:
    push    ebp
    mov     ebp, esp ;salvando o contexto da pilha
    
    push    eax; guardo a quantidade a ser impressa
    
    mov     ecx, MsgLidos1
    mov     edx, lenMsgLidos1
    mov     ebx, 1 
    mov     eax, 4 
    int     0x80             ;foram lidos ...
    
    call    output      ;imprimir a quantidade lida
    
    mov     ecx, MsgLidos2
    mov     edx, lenMsgLidos2
    mov     ebx, 1 
    mov     eax, 4 
    int     0x80             ;foram lidos ...
    
    pop     ebp
    ret
;;;;;SAIDA impQtdBytes

;-------------------------------------------------------------------------------
;;;;;INICIO linefeed
lineFeedF: 
    push    ebp
    mov     ebp, esp ;salvando o contexto da pilha
    
    push    eax
    
    mov     ecx, lineFeed
    mov     edx, lenLineFeed
    mov     ebx, 1 
    mov     eax, 4 
    int     0x80             ;imprimir resultad
    
    pop     eax ; salvando o eax
    
    pop     ebp
    ret
;;;;;FIM lineFeedF

;-------------------------------------------------------------------------------
;;;;;INICIO s_output
soutput:
    push    ebp
    mov     ebp, esp ;salvando o contexto da pilha
    
        mov     eax, dword [ebp+8]
        mov     [ind], eax          ; indice de quantos bytes ler
        
        mov     eax, dword [ebp+12]
        
        mov     ecx, eax
        mov     edx, [ind]
        mov     ebx, 1 
        mov     eax, 4 
        int     0x80             ;imprimir resultad
    
    mov     eax, [ind]
    
    pop     ebp
    ret     
;;;;;FIM s_output

;-------------------------------------------------------------------------------
;;;;;INICIO sinput
sinput:
    push    ebp
    mov     ebp, esp ;salvando o contexto da pilha
    
        mov     eax, dword [ebp+8]
        mov     [ind], eax          ; indice de quantos bytes ler
        
        mov     eax, dword [ebp+12]
        
        mov     ecx, eax
        mov     edx, [ind]
        mov     ebx, 0 
        mov     eax, 3 
        int     0x80             ;imprimir resultado
    
    mov     eax, [ind]

    pop     ebp
    ret     
;;;;;FIM sinput


_start:

    call input
    mov [VAR_22], ebx
    call impQtdBytes

    mov eax, [VAR_24]
    mov [VAR_23], EAX  ;COPY

LABEL_5:
    mov edx, [VAR_22] ; LOAD

    mov eax, edx
    mov ebx, [VAR_23]
    mul ebx
    mov edx, eax ; MUL

    mov [VAR_23], edx ;STORE

    mov edx, [VAR_22] ; LOAD

    sub edx, [VAR_24] ; SUB

    mov [VAR_22], edx ;STORE

    cmp edx, dword 0
    jg LABEL_5

    push dword [VAR_23]
    call output
    call lineFeedF
    call impQtdBytes


    mov ebx, 0
    mov eax, 1
    int 0x80 ; STOP

section .data ; CONST
     VAR_24 dd 1

     MsgLidos1 db "Foram lidos/escritos "
     lenMsgLidos1 equ $ - MsgLidos1
     MsgLidos2 db " bytes", 0dH, 0aH 
     lenMsgLidos2 equ $ - MsgLidos2
     lineFeed   db 0dH, 0aH
     lenLineFeed equ $ - lineFeed

section .bss ; SPACE
     VAR_22 resd 1
     VAR_23 resd 1

     ind   resb 1        ;utilizado para o indice dos loops
     temp    resd 1      ;utilizado para impressão leitura temporaria
     valorOutput resd 1  ;utilizado para valores na escrita;
     valorInput resd 1   ;utilizado para valores da leitura
     buffer   resd 20     ;espaço extra para mostrar números grandes e strings

