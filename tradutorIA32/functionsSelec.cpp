//Módulo de definição das funções utilizadas no tradutor

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
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

//Função converte int para string com representação variável
string convIntStrLabel(int arg){
    stringstream ss;
    ss << arg;
    string str = ss.str();
    str = "LABEL_"+str;

    return str;
}

//Função análisa funções que recebem nenhum argumento STOP
vector<string> geraSemArgumento(vector<string> vecSaida, int arg1){
    if(arg1 == 14){
        vecSaida.push_back("\n    mov ebx, 0\n    mov eax, 1\n    int 0x80 ; STOP\n\n");
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
           vecSaida.push_back("    add edx, ["+strArg2+"] ; ADD\n\n");

           break;
        case 2:
           vecSaida.push_back("    sub edx, ["+strArg2+"] ; SUB\n\n");
           break;
        case 3:
            ///Preciso alterar para fazer handle de oversingend
            vecSaida.push_back("    mov eax, edx\n    mov ebx, ["+strArg2+"]\n    mul ebx\n    mov edx, eax ; MUL\n\n");
            break;
        case 4:
            vecSaida.push_back("    mov eax, edx\n    mov ebx, ["+strArg2+"]\n    xor edx, edx\n    idiv ebx\n    mov edx, eax ; DIV\n\n");
            break;
        case 10:
            vecSaida.push_back("    mov edx, ["+strArg2+"] ; LOAD\n\n");
            break;
        case 11:
            vecSaida.push_back("    mov ["+strArg2+"], edx ;STORE\n\n");
            break;
        case 12:
            vecSaida.push_back("    call input\n    mov ["+strArg2+"], ebx\n    call impQtdBytes\n\n");
            break;
        case 13:
            vecSaida.push_back("    push dword ["+strArg2+"]\n    call output\n    call lineFeedF\n    call impQtdBytes\n\n");
            break;
      }

    return vecSaida;
}

//Função lida com os jumps e deslocamentos de código
vector<string> geraDeslocamento(vector<string> vecSaida, vector<int> vecInd, int arg1, int arg2){
    string strArg2 = convIntStrLabel(arg2);

    //correcao do indice
    int temp;
    for(int i =0; i<vecInd.size(); i++){
        if(arg2 == vecInd[i]){
            temp = i+1;
            break;
        }
    }

    //Switch para a instrução recebida
    switch ( arg1 ){
    case 5:
        vecSaida.insert(vecSaida.begin()+temp, strArg2+":\n");
        vecSaida.push_back("    jmp "+strArg2+"\n\n");
        break;
    case 6:
        vecSaida.insert(vecSaida.begin()+temp, strArg2+":\n");
        vecSaida.push_back("    cmp edx, dword 0\n    jl "+strArg2+"\n\n");
        break;
    case 7:
        vecSaida.insert(vecSaida.begin()+temp, strArg2+":\n");
        vecSaida.push_back("    cmp edx, dword 0\n    jg "+strArg2+"\n\n");
        break;
    case 8:
        vecSaida.insert(vecSaida.begin()+temp, strArg2+":\n");
        vecSaida.push_back("    cmp edx, dword 0\n    jz "+strArg2+"\n\n");
        break;
    }

    return vecSaida;
}

//Função análisa as funções assembly qye recebem 2 argumentos: COPY, SINPUT, SOUTPUT
vector<string> geraDoisArgumento(vector<string> vecSaida, int arg1, int arg2, int arg3){
    string strArg2 = convIntStr(arg2);
    string strArg3 = convIntStr(arg3);

    //Switch para o case de 2 argumentos
    switch ( arg1 )
      {
        case 9:
            vecSaida.push_back("    mov eax, ["+strArg2+"]\n    mov ["+strArg3+"], EAX  ;COPY\n\n");
            break;
        case 15: //call SINPUT
            vecSaida.push_back("    push dword "+strArg2+"\n    push dword "+strArg3.substr(4, strArg3.size()-1)+"\n    call sinput\n    call impQtdBytes\n\n");
            break;
        case 16:
            vecSaida.push_back("    push dword "+strArg2+"\n    push dword "+strArg3.substr(4, strArg3.size()-1)+"\n    call soutput\n    call lineFeedF\n    call impQtdBytes\n\n");
            break;
      }

    return vecSaida;
}

//Função para gerar secao .data
vector<string> sectionDataHandle(vector<string> vecSaida,int ind, int arg1){
    string strInd = convIntStr(ind);
    string strArg1 = convIntStr(arg1);
    strInd = "     "+strInd + " dd "  + strArg1.substr(4, strArg1.size())+"\n";
    vecSaida.push_back(strInd);

    return vecSaida;
}

//Função para gerar secao .bss
vector<string> sectionBssHandle (vector<string> vecSaida,int ind, int arg1){
    string strArg1 = convIntStr(ind);
    strArg1 = "     "+strArg1 + " resd 1\n";
    vecSaida.push_back(strArg1);

    return vecSaida;
}

//Função para gerar seção .bss com SPACE X
vector<string> sectionBssHandleX (vector<string> vecSaida,int ind, int arg1){
    string strArg1 = convIntStr(ind);
    string strArg2 = convIntStr(arg1);
    strArg1 = "     "+strArg1 + " resb " +strArg2.substr(4, strArg2.size()-1)+"\n";
    vecSaida.push_back(strArg1);

    return vecSaida;
}

//Função insere as funções desenvolvidas em x86
vector<string> insereBaseIO(){
    //abro arquivo
    string str_arq1("baseInputOutput.txt");

    //abertura dos arquivos recebidos
    ifstream arq1(str_arq1.c_str());

    //casonão seja possível abrir o arquivo 1
        if(!arq1){
            cout<<"Arquivo de funcoes nao encontrado: "<< str_arq1 << endl;
            exit(-1);
        }

    string line;
    vector<string> arq1_vector;

    while(getline(arq1, line)){
        arq1_vector.push_back(line+"\n");
    }

    arq1.close();

    return arq1_vector;
}


