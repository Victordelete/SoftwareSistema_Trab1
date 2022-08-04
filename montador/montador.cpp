/*
Programa desenvolvido para a o primeiro trabalho (T1) para a
disciplina de Software Básico (Software de Sistema)
na Universidade de Brasília.

Tempo Gasto:
    Aproximadamente 17 horas.

Desenvolvedores:
    Daniel - xxxxxxxxx
    Victor Hugo Marques Vieira - 150047649

    a chamada do programa é do tipo:
    ./montador -o nomeArquivoEntrada nomeArquivoSaida

    -p ou -o: o primeiro para processar o segundo para montar o arquivo recebido
*/

#include <stdio.h>
#include <string.h>

#include "pre_processamento.cpp"
#include "pri_passagem.c"
#include "seg_passagem.c"

#include "list_instrucoes.c"

///Função principal
//int main(char* nome_arquivo, char tipo_abert){
int main( int argc, char *argv[], char *envp[] ){

    //teste de arqumentos
    if(argc != 4){
        cout<<"Quantidade incorreta de argumentos.\n";
        return -1;
    }

    //nome do arquivo a ser compilado
    char tipo = argv[1][1];
    char nome_arquivo[99]; strcpy(nome_arquivo, argv[2]);
    char nome_arquivo_saida[99]; strcpy(nome_arquivo_saida, argv[3]);

    if(tipo != 'p' && tipo != 'o'){
        cout<<"Tipo de chamada não conhecido.\n\n";
        return -1;
    }


    // ponteiro para arquivo onde ficará o arquivo base
    FILE *arq_mont;

    //nome do programa recebido
    arq_mont = fopen(nome_arquivo, "r");//////////LEMBRAR DE RETIRAR ESSA CHAMADA

    //testando se o arquivo foi aberto com sucesso
    if(arq_mont == NULL){
        printf("Erro na abertura do arquivo!\n");
        return -1;
    }
    fclose(arq_mont); //fecho arquivo para ser reaberto no módulo

    //cada etapa é realizada de forma separada recebendo o nome do arquivo necessário
    pre_processamento(nome_arquivo, nome_arquivo_saida);

    return(0);
}
