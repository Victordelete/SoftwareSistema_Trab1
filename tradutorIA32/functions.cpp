//Módulo de definição das funções utilizadas no ligador

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

#include "functions.h"

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


vector<string> tradutor(vector<int> vecCodigo){
    int ind = 0;
    vector<string> vecSaida;

    while(ind < vecCodigo.size()){
        cout<<vecCodigo[ind]<<" ";

        //CAso que o opcode recebe 1 argumento: STOP.
        if(vecCodigo[ind] == 14){

        }
        //Caso que o opcode recebe 3 argumentos: COPY, S_INPUT, S_OUTPUT
        if(vecCodigo[ind] == 9 || vecCodigo[ind] == 15 || vecCodigo[ind] == 16 ){
            continue;
        }
        //Caso que o opcode recebe 3 argumentos: INPUT, OUTPUT
        if( vecCodigo[ind] == 12 || vecCodigo[ind] == 13 ){
            continue;
        }

    }

    return vecSaida;
}
