/*
Programa desenvolvido para a o primeiro trabalho (T1) para a
disciplina de Software B�sico (Software de Sistema)
na Universidade de Bras�lia.

Ligador

Tempo Gasto:
    Aproximadamente 4 horas.

Desenvolvedores:
    Daniel - xxxxxxxxx
    Victor Hugo Marques Vieira - 150047649
*/

#include "functions.cpp"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int main(){
    string str_arq1("fat mod A.v");
    string str_arq2("fat mod B.v");
    string line;
    vector<string> arq1_vector;
    vector<string> arq2_vector;

    //abertura dos arquivos recebidos
    ifstream arq1(str_arq1.c_str());
    //cason�o seja poss�vel abrir o arquivo 1
        if(!arq1){
            cout<<"Nao foi possivel abrir o arquivo: "<< str_arq1 << endl;
            return -1;
        }
    ifstream arq2(str_arq2.c_str());
        //cason�o seja poss�vel abrir o arquivo 2
        if(!arq2){
            cout<<"Nao foi possivel abrir o arquivo: "<< str_arq2<< endl;
            return -1;
        }

    //trabalho com os arquivos em vector de string para facilitar o acesso
    while(getline(arq1, line)){
        arq1_vector.push_back(line);
    }

    //trabalho com os arquivos em vector de string para facilitar o acesso
    while(getline(arq2, line)){
        arq2_vector.push_back(line);
    }

    arq1.close();
    arq2.close(); //fecho os arquivos abertos

    //iniciando tabelas utilizadas para liga��o
    //Inicialmente para dois arquivos s�o necess�rios somente tabUso1 e tabDef2, por�m vou iniciar tudo
    //para facilitar a detec��o de erros.
    vector<tabela> tabUso1 = iniciaTabUso(arq1_vector);
        //imprimi(tabUso1, "TABELA USO");
    vector<tabela> tabDef1 = iniciaTabDef(arq1_vector);
        //imprimi(tabDef1, "TABELA DEF");
    vector<int> mont1= iniciaTabMont(arq1_vector);
        //imprimiVecInt(mont1, "CODIGO OBJETO");

    vector<tabela> tabUso2 = iniciaTabUso(arq2_vector);
        //imprimi(tabUso2, "TABELA USO");
    vector<tabela> tabDef2 = iniciaTabDef(arq2_vector);
        //imprimi(tabDef2, "TABELA DEF");
    vector<int> mont2= iniciaTabMont(arq2_vector);
        //imprimiVecInt(mont2, "CODIGO OBJETO");

    vector<int> ligFinal = iniciaTabMont (tabUso1,
                                          tabDef1,
                                          mont1,
                                          tabUso2,
                                          tabDef2,
                                          mont2);


    return 0;
}


