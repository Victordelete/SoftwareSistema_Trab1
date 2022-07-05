/*Componente que realiza o pre_processamento do arquivo
a ser montado.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Fun��o recebe nome do arquivo para realizar o pr�-processamento
//Pr�-processamento se d� basicamente pela retirada de espa�os extras
//e coment�rios marcados por ";"
void atualiza_nome_Arquivo(char *arq_sai);

void pre_processamento(char *arq_ent){
    //char arq_ent[] = "arquivo.txt";

    char arq_sai[200]; //tamanho m�ximo para o arquivo (talvez seja necess�rio mudar)
    strcpy(arq_sai, arq_ent);
    atualiza_nome_Arquivo(arq_sai);

    char linha_ent[100]; //string onde as linhas ser�o armazenadas.
    char linha_sai[100];

    // ponteiro para arquivo onde ficar� o arquivo base
    FILE *pont_arq_ent;
    FILE *pont_arq_sai;

    pont_arq_ent = fopen(arq_ent, "r"); //arquivo sempre ser� aberto com sucesso pois j� foi testado com anteced�ncia.
    pont_arq_sai = fopen(arq_sai, "w+"); //crio o arquivo de sa�da

    if(pont_arq_sai == NULL){
        printf("Erro na abertura do arquivo de sa�da!\n");
        return;
    }

    int ind_ent = 0, ind_sai = 0 ;//indice para as strings de entrada e sa�da.
    int last_space=0; // marcador de passagem para dois '\n' seguidos

    while(!feof(pont_arq_ent)){
        //pego uma linha inteira do arquivo de entrada
        fgets(linha_ent, 99, pont_arq_ent);

        //handle para elimina��o de espa�os duplos e coment�rios
        for(ind_ent= 0; ind_ent<strlen(linha_ent); ind_ent++ ){
            //handle coment�rio
            if(linha_ent[ind_ent]== ';'){
                linha_sai[ind_sai]='\n';
                ind_sai++;
                break;
            }

            //handle espa�os extras
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

        //handle para elimina��o de linhas vazias
        if(strlen(linha_sai)== 1){ //caso haja somente '\n' '/0'
            ind_sai = 0;
            linha_sai[0]='\0';
            continue;
        }
        else{
            fputs(linha_sai, pont_arq_sai); //escrevo no arquivo somente os que s�o linhas n�o vazias
        }

        ind_sai=0; //corrijo o �ndice de sa�de.
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

