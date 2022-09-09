//Módulo de definição das funções utilizadas no ligador

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
    string temp = "section .text\n\nglobal _start\n\n_start:\n\n";

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

    vecSaida = iniciaVector(vecSaida);

    while(ind < vecCodigo.size()){

        //Caso que o opcode recebe 0 argumentos: STOP.
        if(vecCodigo[ind] == 14){
            vecSaida = geraSemArgumento(vecSaida, vecCodigo[ind]);
            ind= ind+1;
            continue;
        }

        //Caso que o opcode recebe 2 argumentos: COPY, S_INPUT, S_OUTPUT
        if(vecCodigo[ind] == 9 || vecCodigo[ind] == 15 || vecCodigo[ind] == 16){
            vecSaida = geraDoisArgumento(vecSaida, vecCodigo[ind], vecCodigo[ind+1], vecCodigo[ind+2]);
            ind= ind+3;
            continue;
        }
        //Caso que o opcode recebe 1 argumentos: INPUT, OUTPUT e demais funções do assembly inventado
        else{//( vecCodigo[ind] == 12 || vecCodigo[ind] == 13 ){
            vecSaida = geraUmArgumento(vecSaida, vecCodigo[ind], vecCodigo[ind+1]);
            ind= ind+2;
            continue;
        }
    }
    imprimiVecStr(vecSaida);
    return vecSaida;
}
