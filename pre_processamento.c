/*Componente que realiza o pre_processamento do arquivo
a ser montado.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Função recebe nome do arquivo para realizar o pré-processamento
//Pré-processamento se dá basicamente pela retirada de espaços extras
//e comentários marcados por ";"
void atualiza_nome_Arquivo(char *arq_sai);

void pre_processamento(char *arq_ent){
    //char arq_ent[] = "arquivo.txt";

    char arq_sai[200]; //tamanho máximo para o arquivo (talvez seja necessário mudar)
    strcpy(arq_sai, arq_ent);
    atualiza_nome_Arquivo(arq_sai);

    char linha_ent[100]; //string onde as linhas serão armazenadas.
    char linha_sai[100];

    // ponteiro para arquivo onde ficará o arquivo base
    FILE *pont_arq_ent;
    FILE *pont_arq_sai;

    pont_arq_ent = fopen(arq_ent, "r"); //arquivo sempre será aberto com sucesso pois já foi testado com antecedência.
    pont_arq_sai = fopen(arq_sai, "w+"); //crio o arquivo de saída

    if(pont_arq_sai == NULL){
        printf("Erro na abertura do arquivo de saída!\n");
        return;
    }

    int ind_ent = 0, ind_sai = 0 ;//indice para as strings de entrada e saída.
    int last_space=0; // marcador de passagem para dois '\n' seguidos

    while(!feof(pont_arq_ent)){
        //pego uma linha inteira do arquivo de entrada
        fgets(linha_ent, 99, pont_arq_ent);

        //handle para eliminação de espaços duplos e comentários
        for(ind_ent= 0; ind_ent<strlen(linha_ent); ind_ent++ ){
            //handle comentário
            if(linha_ent[ind_ent]== ';'){
                linha_sai[ind_sai]='\n';
                ind_sai++;
                break;
            }

            //handle espaços extras
            if(linha_ent[ind_ent] ==' '){
                if(last_space==0 && ind_sai!=0){
                    linha_sai[ind_sai] = linha_ent[ind_ent];
                    ind_sai++;
                    last_space=1;
                    continue;
                }
                continue;
            }
            else{
                last_space = 0 ;
            }

            linha_sai[ind_sai] = linha_ent[ind_ent];
            ind_sai++;
        }

        linha_sai[ind_sai] = '\0';

        //handle para eliminação de linhas vazias
        if(strlen(linha_sai)== 1){ //caso haja somente '\n' '/0'
            ind_sai = 0;
            linha_sai[0]='\0';
            continue;
        }
        else{
            fputs(linha_sai, pont_arq_sai); //escrevo no arquivo somente os que são linhas não vazias
        }

        ind_sai=0; //corrijo o índice de saíde.
    }

    fclose(pont_arq_ent);
    fclose(pont_arq_sai);

    return;
}

void atualiza_nome_Arquivo(char *arq_sai){
        char *prefixo_p = ".pre"; //para esse arquivo de preprocessamento
        for(int i=0; i<4; i++){
            arq_sai[strlen(arq_sai) - 4 +i] = prefixo_p[i];
        }
        return;
}

