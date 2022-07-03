/*
Programa desenvolvido para a o primeiro trabalho (T1) para a
disciplina de Software Básico (Software de Sistema)
na Universidade de Brasília.

Tempo Gasto:
    Aproximadamente 15 horas.

Desenvolvedores:
    Daniel - xxxxxxxxx
    Victor Hugo Marques Vieira - 150047649
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pre_processamento.c"
#include "pri_passagem.c"
#include "seg_passagem.c"

///Função principal
//int main(char* nome_arquivo, char tipo_abert){
int main(void){
    //nome do arquivo a ser compilado mudar depois
    char nome_arquivo[] = "arquivo.txt";

    // ponteiro para arquivo onde ficará o arquivo base
    FILE *arq_mont;

    //nome do programa recebido
    arq_mont = fopen(nome_arquivo, "r"); //////////LEMBRAR DE RETIRAR ESSA CHAMADA

    //testando se o arquivo foi aberto com sucesso
    if(arq_mont == NULL){
        printf("Erro na abertura do arquivo!\n");
        return -1;
    }

    //cada etapa é realizada de forma separada alterando o vetor de struct
    pre_processamento();
    pri_passagem();
    seg_passagem();

    return(0);
}
