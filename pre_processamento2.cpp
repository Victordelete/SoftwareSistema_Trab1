/*Componente que realiza o pre_processamento do arquivo
a ser montado.
*/

//Função recebe nome do arquivo para realizar o pré-processamento
//Pré-processamento se dá basicamente pela retirada de espaços extras
//e comentários marcados por ";"

//todo o arquivo é pré-processado para facilitar análise, e após isso
//são análisada a presensa das diretivas de pré processamento

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
    using namespace std;

class saidaClass{
    public:
        int numLinha; //número da linha no arquivo original
        string contLinha; //conteúdo da linha
        saidaClass(){}

        saidaClass(string contLinha, int numLinha){
            this->numLinha = numLinha;
            this->contLinha = contLinha;
        }

        ///setter and getters
        int getNumLinha(){
            return this->numLinha;
        }
        string getContLinha(){
            return this->contLinha;
        }
        void setNumLinha(int numLinha){
            this->numLinha = numLinha;
        }
        void setContLinha(string contLinha){
            this->contLinha = contLinha;
        }
};

void atualiza_nome_Arquivo(char *arq_sai);
void imprimiVectorSaidaClass(vector<saidaClass> vectorSaida);
void diretivaPreProcessamento(vector<saidaClass> vectorSaida);

void pre_processamento(char *arq_ent){
    //char arq_ent[] = "arquivo.txt";

    char arq_sai[200]; //tamanho máximo para o arquivo (talvez seja necessário mudar)
    strcpy(arq_sai, arq_ent);
    atualiza_nome_Arquivo(arq_sai);

    vector<saidaClass> vectorSaida;
    vector<saidaClass>::iterator it;
        saidaClass modeloSaida;

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

    int numLinha=0;
    while(!feof(pont_arq_ent)){
        //pego uma linha inteira do arquivo de entrada
        fgets(linha_ent, 99, pont_arq_ent);
        numLinha++;

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
            //caso o caractere seja o esperado passo para maiusculo e copio para minha linha de saída
            linha_sai[ind_sai] = toupper(linha_ent[ind_ent]);
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
            modeloSaida.setContLinha(linha_sai);
            modeloSaida.setNumLinha(numLinha);
            vectorSaida.push_back(modeloSaida);
        }

        ind_sai=0; //corrijo o índice de saída.
    }

    //imprimiVectorSaidaClass(vectorSaida);
    diretivaPreProcessamento(vectorSaida);

    fclose(pont_arq_ent);
    fclose(pont_arq_sai);

    return;
}

void atualiza_nome_Arquivo(char *arq_sai){
        char prefixo_p[] = ".pre"; //para esse arquivo de preprocessamento
        for(int i=0; i<4; i++){
            arq_sai[strlen(arq_sai) - 4 +i] = prefixo_p[i];
        }
        return;
}

void diretivaPreProcessamento(vector<saidaClass> vectorSaida){
    //crio as diretivas utilizas no pré-processamento
    //desta forma estou lidando somente com as diretivas abordadas no pré-processamento.
    string strIf = "IF";
    string strEqu = "EQU";

    //vector utilizado para guardar as diretivas EQU para sstring e NumLinha para seu valor
    vector<saidaClass> vectorDir;
    vector<saidaClass>::iterator it;
            saidaClass modeloSaida;

    string strTemp; //string temporaria pra análise

    bool secaoTextoB =false; //marcador de antes e depois da SECAO TEXTO

    int ind = 0;
    for(int i=0; i<vectorSaida.size(); i++){
        strTemp = vectorSaida[i].getContLinha() ; //atualizo variável temporária

        if(strTemp == "SECAO TEXTO\n")
            secaoTextoB = true;

        //análise antes do SECAO TEXTO
        if(!secaoTextoB){
            //as diretivas sempre são corretas, logo posso simplesmente assumir que foi feito corretamente
            ind = strTemp.find(" ");
            modeloSaida.setContLinha(strTemp.substr(0,ind-1));
            stringstream(strTemp.substr(ind+5, strTemp.size()))>>ind;
            modeloSaida.setNumLinha(ind);
            vectorDir.push_back(modeloSaida);
        }
        //análise após a SECAO TEXTO
        else{
            ind = strTemp.find(" ");
            strTemp = strTemp.substr(0, ind);
        }
    }
    imprimiVectorSaidaClass(vectorDir);

    return;
}

void imprimiVectorSaidaClass(vector<saidaClass> vectorSaida){
    for(int i=0; i<vectorSaida.size(); i++){
        cout<< vectorSaida[i].getNumLinha() << " " << vectorSaida[i].getContLinha()<<"\n";
    }
    return;
}

