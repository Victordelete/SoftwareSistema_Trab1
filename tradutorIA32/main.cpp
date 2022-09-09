/*
Programa desenvolvido para o segundo trabalho (T2) para a
disciplina de Software Básico (Software de Sistema)
na Universidade de Brasília.

Tradutor de código máquina para IA32.

Tempo Gasto:


Desenvolvedores:
    Daniel do Carmo Figueirêdo -  160057922
    Victor Hugo Marques - 150047649

*/

#include "functions.cpp"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

int main( ){
    //teste de arqumentos
    /*if(argc < 3){
        cout<<"Quantidade incorreta de argumentos.\n";
        return -1;
    }

    string str_arq1 = argv[1];
    string str_arq2 = argv[2];
    */

    string str_arq1("arquivo.obj");

    string line;
    vector<string> arq1_vector;

    //abertura dos arquivos recebidos
    ifstream arq1(str_arq1.c_str());

    //casonão seja possível abrir o arquivo 1
        if(!arq1){
            cout<<"Nao foi possivel abrir o arquivo: "<< str_arq1 << endl;
            return -1;
        }

    //trabalho com os arquivos em vector de string para facilitar o acesso
    while(getline(arq1, line)){
        arq1_vector.push_back(line);
    }

    arq1.close();

    vector<int> codigoInteiro = convertInteiro(arq1_vector[0]);

    vector<string> codigoTraduzido = tradutor(codigoInteiro);

    //Criando arquivo de saída
    string str_arqSaida = str_arq1.substr(0, str_arq1.size()-3) + "s";
    string saida;
    ofstream arqSaida;
    arqSaida.open(str_arqSaida.c_str());

    for(const auto &linha : codigoTraduzido){
        arqSaida<<linha;
    }

    arqSaida.close();

    return 0;
}
