/*
Programa desenvolvido para a o primeiro trabalho (T1) para a
disciplina de Software Básico (Software de Sistema)
na Universidade de Brasília.

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
    imprimi();
    string line;
    vector<string> arq1_vector;
    vector<string> arq2_vector;

    //abertura dos arquivos recebidos
    ifstream arq1(str_arq1.c_str());
    //casonão seja possível abrir o arquivo 1
        if(!arq1){
            cout<<"Nao foi possivel abrir o arquivo: "<< str_arq1 << endl;
            return -1;
        }
    ifstream arq2(str_arq2.c_str());
        //casonão seja possível abrir o arquivo 2
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

    //iniciando tabelas utilizadas para ligação
    //Inicialmente para dois arquivos são necessários somente tabUso1 e tabDef2, porém vou iniciar tudo
    //para facilitar a detecção de erros.
    vector<tabela> tabUso1 = iniciaTabUso(arq1_vector);
    vector<tabela> tabDef1 = iniciaTabDef(arq1_vector);
    vector<int> mont1= iniciaTabMont(arq1_vector);

    vector<tabela> tabUso2 = iniciaTabUso(arq2_vector);
    vector<tabela> tabDef2 = iniciaTabDef(arq2_vector);
    vector<int> mont2= iniciaTabMont(arq2_vector);


    return 0;
}


