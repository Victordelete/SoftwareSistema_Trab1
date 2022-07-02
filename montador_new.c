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

///Iniciando vetor com opcodes/instruções
//struct para o vetor com informçaão das instruções
struct nome_instrucoes {
    char nome_inst[20];
    int operandos;
    int opcode;
    int tamanho;
};
struct nome_instrucoes vetor_inst[15]; //tamanho fixo de instruções
void inicia_vetor_inst();

///Função principal
//int main(char* nome_arquivo, char tipo_abert){
int main(void){
    //nome do arquivo a ser compilado mudar depois
    char nome_arquivo[] = "arquivo.txt";

    // ponteiro para arquivo onde ficará o arquivo base
    FILE *arq_mont;

    //nome do programa recebido
    arq_mont = fopen(nome_arquivo, "r"); //////////LEMBRAR DE RETIRAR ESSA CHAMADA

    //testando se o arquivo foi realmente aberto
    if(arq_mont == NULL){
        printf("Erro na abertura do arquivo!\n");
        return -1;
    }

    //string para as leituras do arquivo recebido
    char texto_str[50];

    //variavel para controle do tamanho
    int i = 1;

    //cada etapa é realizada de forma separada, com um arquivo de saída diferente
    pre_processamento();

    return(0);
}
