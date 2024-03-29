/*
Programa desenvolvido para a o primeiro trabalho (T1) para a
disciplina de Software B�sico (Software de Sistema)
na Universidade de Bras�lia.

Ligador

Tempo Gasto:
    Aproximadamente 6 horas.

Desenvolvedores:
    Daniel do Carmo Figueir�do -  160057922
    Victor Hugo Marques - 150047649


    Modelo de chamada no terminal windows utilizado para os testes realizados:
    ./ligador arquivoEntrada1.o arquivoEntrada2.o
        A sa�da ser� um arquivo chamada arquivoLigado.o para todos os casos.
        optou-se por esse padr�o porque a descri��o do trabalho n�o tr�s um padr�o de nome
        para o ligador.


    O ligador recebe o valor 0 nos endere�os de mem�ria ainda n�o montados
    por motivo de refer�ncia.
    Importante que as tabelas de def tragam a defini��o do pr�prio m�dulo.
        Exemplo:
        TABELA DEF
        MOD_A 0

        Os arquivos de testes seguem o padr�o, consultar para refer�ncia.
*/

#include "functions.cpp"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

int main( int argc, char *argv[], char *envp[] ){
    //teste de arqumentos
    if(argc < 3){
        cout<<"Quantidade incorreta de argumentos.\n";
        return -1;
    }

    string str_arq1 = argv[1];
    string str_arq2 = argv[2];

    //strings que acompanham o programa para teste
    //string str_arq1("modA.o");
    //string str_arq2("modB.o");

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


    //imprimiVecInt(ligFinal, "SAIDA:");

    string str_arqSaida = "ArquivoLigado.o";
    string saida;
    ofstream arqSaida;
    arqSaida.open(str_arqSaida.c_str());

    int i =0;
    string temp;
    std::ostringstream sstream;

    while(true){
        if(i == ligFinal.size())
            break;
        sstream << ligFinal[i];
        //cout<<sstream.str()<<"\n";
        saida = saida + sstream.str();

        saida = saida + " ";
        sstream.str("");
        i++;
    }

    cout<<saida;
    arqSaida<<saida;

    arqSaida.close();

    return 0;
}
