//Módulo de definição das funções utilizadas no ligador

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

#include "functionsSelec.h"

//Função converte int para string com representação variável
string convIntStr(int arg){
    stringstream ss;
    ss << arg;
    string str = ss.str();
    str = "VAR_"+str;

    return str;
}

//Função análisa funções que recebem nenhum argumento STOP
vector<string> geraSemArgumento(vector<string> vecSaida, int arg1){
    if(arg1 == 14){
        vecSaida.push_back("    mov eax, 1\n    int 0x80 ; STOP\n");
    }
    return vecSaida;
}

//Função análisa as funções assembly que recebem somente um agumento: a maioria
vector<string> geraUmArgumento(vector<string> vecSaida, int arg1, int arg2){
    string strArg2 = convIntStr(arg2);

    //Switch para a instrução recebida
    switch ( arg1 )
      {
        case 1:
           vecSaida.push_back("    add edx, "+strArg2+" ; ADD\n");

           break;
        case 2:
           vecSaida.push_back("    sub edx, "+strArg2+" ; SUB\n");
           break;
        case 3:
            ///Preciso alterar para fazer handle de oversingend
            vecSaida.push_back("    mul edx, "+strArg2+" ; MUL\n");
            break;
        case 4:
            vecSaida.push_back("    add edx, "+strArg2+" ; DIV\n");
            break;
        case 10:
            vecSaida.push_back("    mov edx, "+strArg2+" ; LOAD\n");
            break;
        case 11:
            vecSaida.push_back("    mov "+strArg2+", edx ;STORE\n");
            break;
        case 12:
            vecSaida.push_back("    Input ; INPUT\n");
            break;
        case 13:
            vecSaida.push_back("    Output ; OUTPUT\n");
            break;
      }

    return vecSaida;
}

//Função análisa as funções assembly qye recebem 2 argumentos: COPY, SINPUT, SOUTPUT
vector<string> geraDoisArgumento(vector<string> vecSaida, int arg1, int arg2, int arg3){
    //Switch para o case de 2 argumentos
    switch ( arg1 )
      {
        case 9:
            vecSaida.push_back("    xchg arg2, arg3 ; COPY\n");
            break;
        case 15:
            vecSaida.push_back("    S_INPUT arg2, arg3 ; INPUT STRING");
            break;
        case 16:
            vecSaida.push_back("    S_OUTPUT arg2, arg3 ; OUTPUT STRING");
            break;
      }

    return vecSaida;
}
