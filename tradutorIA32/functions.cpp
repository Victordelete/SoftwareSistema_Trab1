//M�dulo de defini��o das fun��es utilizadas no ligador

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

#include "functions.h"
#include "functionsSelec.cpp"

//fun��o utilizada para testes durante desenvolvimento
void imprimiVecStr(vector<string> vecSaida){
    for(const auto &linha : vecSaida){
        cout<<linha;
    }
    return;
}

//Inicia o vetor de resultado para a tradu��o
vector<string> iniciaVector(vector<string> vecSaida){
    //Essa fun��o ir� adicionar tamb�m as fun��es inicia
    string temp = "section .text\n\nglobal _start\n\n_start:\n\n";

    vecSaida.insert( vecSaida.begin() , temp);

    return vecSaida;
}

//Fun��o recebe string com o codigo objeto e retorna vector<int> com as instru��es
//e endere�os.
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

//Fun��o que faz a sele��o inicial para tradu��o
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
        //Caso que o opcode recebe 1 argumentos: INPUT, OUTPUT e demais fun��es do assembly inventado
        else{//( vecCodigo[ind] == 12 || vecCodigo[ind] == 13 ){
            vecSaida = geraUmArgumento(vecSaida, vecCodigo[ind], vecCodigo[ind+1]);
            ind= ind+2;
            continue;
        }
    }
    imprimiVecStr(vecSaida);
    return vecSaida;
}
