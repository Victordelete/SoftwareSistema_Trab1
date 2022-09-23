//Módulo de definição das funções utilizadas no tradutor

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

#include "functions.h"
#include "functionsSelec.cpp"

//função utilizada para testes durante desenvolvimento
void imprimiVecStr(vector<string> vecSaida){
    for(const auto &linha : vecSaida){
        cout<<linha;
    }
    return;
}

//Inicia o vetor de resultado para a tradução
vector<string> iniciaVector(vector<string> vecSaida){
    //Essa função irá adicionar também as funções inicia
    //string temp = "section .text\n\nglobal _start\n\n_start:\n\n";
    string temp = "\n\n_start:\n\n";

    vecSaida.insert( vecSaida.begin() , temp);

    return vecSaida;
}

//Função recebe string com o codigo objeto e retorna vector<int> com as instruções
//e endereços.
vector<int> convertInteiro(string strCodigo){
    int ind = 0;
    int temp = 0;
    vector<int> vecSaida;

    while(true ){
        ind = strCodigo.find(" ");
            if(ind == -1){
                ind = strCodigo.size();
                stringstream(strCodigo.substr(0, ind) )>>temp;
                vecSaida.push_back(temp);
                break;
            }
        stringstream(strCodigo.substr(0, ind))>>temp;
        strCodigo = strCodigo.substr(ind+1, strCodigo.size());
        vecSaida.push_back(temp);
    }
    return vecSaida;
}

//Função que faz a seleção inicial para tradução
vector<string> tradutor(vector<int> vecCodigo){
    int ind = 0;
    vector<string> vecSaida;
    vector<int> vecInd;

    vecSaida = iniciaVector(vecSaida);

    while(ind < vecCodigo.size()){

        //Caso que o opcode recebe 0 argumentos: STOP.
        if(vecCodigo[ind] == 14){
                vecInd.push_back(ind);
            vecSaida = geraSemArgumento(vecSaida, vecCodigo[ind]);
            ind= ind+1;
            break; //Se achar um break para o loop e vou para o loop de dados
        }

        //Caso de deslocamento no código
        if(vecCodigo[ind]== 5 || vecCodigo[ind]== 6 || vecCodigo[ind]== 7 || vecCodigo[ind]== 8){
                vecInd.push_back(ind);
            vecSaida = geraDeslocamento(vecSaida,vecInd, vecCodigo[ind], vecCodigo[ind+1]);
            ind = ind +2;
            continue;
        }

        //Caso que o opcode recebe 2 argumentos: COPY, S_INPUT, S_OUTPUT
        if(vecCodigo[ind] == 9 || vecCodigo[ind] == 15 || vecCodigo[ind] == 16){
                vecInd.push_back(ind);
            vecSaida = geraDoisArgumento(vecSaida, vecCodigo[ind], vecCodigo[ind+1], vecCodigo[ind+2]);
            ind= ind+3;
            continue;
        }
        //Caso que o opcode recebe 1 argumentos: INPUT, OUTPUT e demais funções do assembly inventado
        else{
                vecInd.push_back(ind);
            vecSaida = geraUmArgumento(vecSaida, vecCodigo[ind], vecCodigo[ind+1]);
            ind= ind+2;
            continue;
        }
    }

    //Lido com a secao .data
    vecSaida.push_back("section .data ; CONST\n");
    for(int i =ind; i<vecCodigo.size(); i++){
        if(vecCodigo[i-1] == -1)
            continue;

        if(vecCodigo[i]!= 0 && vecCodigo[i]>0){ //mesma lógica porém deixei para relembrar o histórico
            vecSaida = sectionDataHandle(vecSaida, i, vecCodigo[i]);
        }
    }
    ///CONSTANTES DE IMPRESSÃO
    vecSaida.push_back("\n");
    vecSaida.push_back("     MsgLidos1 db \"Foram lidos/escritos \"\n");
    vecSaida.push_back("     lenMsgLidos1 equ $ - MsgLidos1\n");
    vecSaida.push_back("     MsgLidos2 db \" bytes\", 0dH, 0aH \n");
    vecSaida.push_back("     lenMsgLidos2 equ $ - MsgLidos2\n");
    vecSaida.push_back("     lineFeed   db 0dH, 0aH\n");
    vecSaida.push_back("     lenLineFeed equ $ - lineFeed\n\n");

    //Lido com a secao .bss
    vecSaida.push_back("section .bss ; SPACE\n");
    for(int i =ind; i<vecCodigo.size(); i++){
        if(vecCodigo[i]== 0){
            vecSaida = sectionBssHandle(vecSaida, i, vecCodigo[i]);
        }
        //é preciso diferenciar quando há variás labels ou uma única label com vários pontos
        if(vecCodigo[i] == -1){
            //neste caso este número é o indicio de inicio de SPACE X, e i+1 é a quantidade
            vecSaida = sectionBssHandleX(vecSaida, i, vecCodigo[i+1]);
            i++;
        }
    }

    ///VARIAVEIS DAS FUNÇÕES
    vecSaida.push_back("\n");
    vecSaida.push_back("     ind   resb 1        ;utilizado para o indice dos loops\n");
    vecSaida.push_back("     temp    resd 1      ;utilizado para impressão leitura temporaria\n");
    vecSaida.push_back("     valorOutput resd 1  ;utilizado para valores na escrita;\n");
    vecSaida.push_back("     valorInput resd 1   ;utilizado para valores da leitura\n");
    vecSaida.push_back("     buffer   resd 20     ;espaço extra para mostrar números grandes e strings\n\n");

    vector<string> vecBaseIo;
    vecBaseIo = insereBaseIO();

     for(const auto &linha : vecSaida){
        vecBaseIo.push_back(linha);
    }
    ///imprimir o vector de saida duante os testes
    imprimiVecStr(vecBaseIo);

    return vecBaseIo;
}
