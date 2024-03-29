/*Componente que realiza o pre_processamento do arquivo
a ser montado.
*/

//Fun��o recebe nome do arquivo para realizar o pr�-processamento
//Pr�-processamento se d� basicamente pela retirada de espa�os extras
//e coment�rios marcados por ";"

//todo o arquivo � pr�-processado para facilitar an�lise, e ap�s isso
//s�o an�lisada a presensa das diretivas de pr� processamento

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
        int numLinha; //n�mero da linha no arquivo original
        string contLinha; //conte�do da linha
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

void imprimiVectorSaidaClass(vector<saidaClass> vectorSaida);
void diretivaPreProcessamento(vector<saidaClass> vectorSaida , char *arq_sai);

void pre_processamento(char *arq_ent, char *arq_sai){
    //char arq_ent[] = "arquivo.txt";

    //char arq_sai[200]; //tamanho m�ximo para o arquivo (talvez seja necess�rio mudar)
    //strcpy(arq_sai, arq_ent);
    //atualiza_nome_Arquivo(arq_sai);

    vector<saidaClass> vectorSaida;
    vector<saidaClass>::iterator it;
        saidaClass modeloSaida;

    char linha_ent[100]; //string onde as linhas ser�o armazenadas.
    char linha_sai[100];

    // ponteiro para arquivo onde ficar� o arquivo base
    FILE *pont_arq_ent;

    cout<<"\n"<<arq_sai<<"\n";

    pont_arq_ent = fopen(arq_ent, "r"); //arquivo sempre ser� aberto com sucesso pois j� foi testado com anteced�ncia.

    int ind_ent = 0, ind_sai = 0 ;//indice para as strings de entrada e sa�da.
    int last_space=0; // marcador de passagem para dois '\n' seguidos

    int numLinha=0;
    while(!feof(pont_arq_ent)){
        //pego uma linha inteira do arquivo de entrada
        fgets(linha_ent, 99, pont_arq_ent);
        numLinha++;

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
            //caso o caractere seja o esperado passo para maiusculo e copio para minha linha de sa�da
            linha_sai[ind_sai] = toupper(linha_ent[ind_ent]);
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
            modeloSaida.setContLinha(linha_sai);
            modeloSaida.setNumLinha(numLinha);
            vectorSaida.push_back(modeloSaida);
        }

        ind_sai=0; //corrijo o �ndice de sa�da.
    }

    //imprimiVectorSaidaClass(vectorSaida);
    diretivaPreProcessamento(vectorSaida, arq_sai);

    fclose(pont_arq_ent);

    return;
}

void diretivaPreProcessamento(vector<saidaClass> vectorSaida , char *arq_sai){
    //crio as diretivas utilizas no pr�-processamento
    //desta forma estou lidando somente com as diretivas abordadas no pr�-processamento.
    string strIf = "IF";
    string strEqu = "EQU";

    //vector utilizado para guardar as diretivas EQU para sstring e NumLinha para seu valor
    vector<saidaClass> vectorDir;
    vector<saidaClass> vectorSaidaAtu; //o vetor de sa�da ser� atualizado
    vector<saidaClass>::iterator it;
            saidaClass modeloSaida;

    string strTemp; //string temporaria pra an�lise

    bool secaoTextoB =false; //marcador de antes e depois da SECAO TEXTO

    int ind = 0;
    int i = -1 ;
    for(int i=0; i<vectorSaida.size(); i++){
    //while(i<vectorSaida.size()){
        //i++;
        strTemp = vectorSaida[i].getContLinha() ; //atualizo vari�vel tempor�ria

        if(strTemp == "SECAO TEXTO\n")
            secaoTextoB = true;

        //an�lise antes do SECAO TEXTO
        if(!secaoTextoB){
            //as diretivas sempre s�o corretas, logo posso simplesmente assumir que foi feito corretamente
            ind = strTemp.find(" ");
            modeloSaida.setContLinha(strTemp.substr(0,ind-1));
            stringstream(strTemp.substr(ind+5, strTemp.size()))>>ind;
            modeloSaida.setNumLinha(ind);
            vectorDir.push_back(modeloSaida); //atualizo minha listas de r�tulos para essas diretivas

        }
        //an�lise ap�s a SECAO TEXTO
        else{
            ind = strTemp.find(" ");
            strTemp = strTemp.substr(0, ind); //pego o primeiro operando da lista
                if(strTemp == strIf){ // caso encontre a diretiva
                    strTemp = vectorSaida[i].getContLinha();
                    strTemp = strTemp.substr(ind+1, strTemp.size()-4); //pego o r�tulo
                    //percorro o vector de r�tulos de diretivas
                    for(int j=0; j<vectorDir.size(); j++){
                        if(strTemp == vectorDir[j].getContLinha()){ //caso o r�tulo exista
                            if(vectorDir[j].getNumLinha() == 0){ //caso o conteudo seja zero pulo uma linha na c�pia
                                i++;
                            }
                            else{
                                continue; //copio a pr�xima linha caso o conte�do do EQU seja diferene de 0
                            }
                            break; //caso encontre eu paro o for
                        }
                    }
                }
                else{ //caso n�o tenha nenhuma diretiva ou a diretiva seja positiva
                    vectorSaidaAtu.push_back(vectorSaida[i]);
                }
        }
    }
    imprimiVectorSaidaClass(vectorSaidaAtu);

    FILE *pont_arq_sai;
    pont_arq_sai = fopen(arq_sai, "w+"); //crio o arquivo de sa�da

    for(int i=0; i<vectorSaidaAtu.size(); i++){
        fputs(vectorSaidaAtu[i].getContLinha().c_str(), pont_arq_sai); //escrevo no arquivo somente os que s�o linhas n�o vazias
    }

        fclose(pont_arq_sai);

    return;
}

void imprimiVectorSaidaClass(vector<saidaClass> vectorSaida){
    for(int i=0; i<vectorSaida.size(); i++){
        cout<< vectorSaida[i].getNumLinha() << " " << vectorSaida[i].getContLinha();//<< "\n";
    }
    return;
}

