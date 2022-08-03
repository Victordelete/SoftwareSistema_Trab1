//M�dulo de defini��o das fun��es utilizadas no ligador

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

#include "functions.h"

//fun��o auxiliar para impress�o das tabelas criadas
void imprimi(vector<tabela> tab, string tipImpressao){
    cout << tipImpressao <<"\n";
    for(int i=0; i<tab.size(); i++){
        cout<<tab[i].simbolo <<":"<<tab[i].valor <<"\n";
    }
    cout<<"\n";
    return;
}

//fun��o auxiliar para impress�o do vector de int da montagem recebidas
void imprimiVecInt(vector<int> vecSaida, string tipImpressao){
    cout<< tipImpressao <<"\n";
    for(int i = 0 ; i<vecSaida.size(); i++){
        cout<<vecSaida[i]<<"_";
    }
    cout<<"\n\n";
    return;
}

//fun��o que retorna a tabela de uso
 vector<tabela> iniciaTabUso(vector<string> arq_vector){
    vector<tabela> tabUso;
    tabela tabtemp;
    bool tabUsoBool = false;

    //percorro todo o vector do meu arquivo
    for(int i=0 ; i<arq_vector.size(); i++){
        //delimito qual � o inicio da minha tabela de uso
        if(arq_vector[i]== "TABELA USO"){
            tabUsoBool = true;
            continue;
        }

        if(tabUsoBool){
                if(arq_vector[i] =="\0") //saio do la�o caso saia da regi�o da tabUso
                    break;
            //coloco os dados lidos em uma vari�vel tempor�ria
            tabtemp.simbolo = arq_vector[i].substr(0, arq_vector[i].find(" "));
            //tabtemp.valor = arq_vector[i].substr(arq_vector[i].find(" ")+1, arq_vector[i].size());
            stringstream(arq_vector[i].substr(arq_vector[i].find(" ")+1, arq_vector[i].size()))>>tabtemp.valor;
            tabUso.push_back(tabtemp); //atualizo meu vector
        }
    }
    return tabUso;
}

//fun��o que retorna a tabela de defini��o
vector<tabela> iniciaTabDef(vector<string> arq_vector){
    vector<tabela> tabDef;
    tabela tabtemp;
    bool tabDefBool = false;

    //percorro todo o vector do meu arquivo
    for(int i=0 ; i<arq_vector.size(); i++){
        //delimito qual � o inicio da minha tabela de uso
        if(arq_vector[i]== "TABELA DEF"){
            tabDefBool = true;
            continue;
        }

        if(tabDefBool){
                if(arq_vector[i] =="\0") //saio do la�o caso saia da regi�o da tabDef
                    break;
            //coloco os dados lidos em uma vari�vel tempor�ria
            tabtemp.simbolo = arq_vector[i].substr(0, arq_vector[i].find(" "));
            //tabtemp.valor = arq_vector[i].substr(arq_vector[i].find(" ")+1, arq_vector[i].size());
            stringstream(arq_vector[i].substr(arq_vector[i].find(" ")+1, arq_vector[i].size()))>>tabtemp.valor;
            tabDef.push_back(tabtemp); //atualizo meu vector
        }
    }
    return tabDef;
}

//fun��o que retorna a pr� montagem dos m�dulos
vector<int> iniciaTabMont(vector<string> arq_vector){
    //estou assumindo que o c�digo montado est� na �ltima linah do arquivo
    string ultLinha = arq_vector[arq_vector.size()-1];
    //cout<<ultLinha<<"\n\n\n";
    int temp;
    vector<int> vecSaida;
    int ind = 0;//indices para pular os espa�os

    while(true ){
        ind = ultLinha.find(" ");
            if(ind == -1){
                //cout<<"final\n";
                //caso n�o encontre � porque a string acabou
                    //if(ultLinha.size() == 0) //se a string for diferente de zero ela acaba e n�o tinha espa�o no final
                      //  break;
                    //caso tivesse espa�o no final eu pego o �ltimo item
                ind = ultLinha.size();
                //cout<<"ind: "<<ind<<"\n";

                //cout<<ultLinha.substr(0,ind) <<"\n";
                stringstream(ultLinha.substr(0, ind) )>>temp;
                //cout<<"temp: "<<temp<<"\n";
                vecSaida.push_back(temp);
                break;
            }
        stringstream(ultLinha.substr(0, ind))>>temp;
        //cout<<"string: "<<ultLinha.substr(0, ind)<<"\n";
        //cout<<"int: "<<temp<<"\n";
        ultLinha = ultLinha.substr(ind+1, ultLinha.size());
        vecSaida.push_back(temp);
    }
    //cout<<"saida \n\n\n";

    return vecSaida;
}

//fun��o que faz a liga��o final das tabelas constru�das
vector<int> iniciaTabMont(vector<tabela> tabUso1,
                          vector<tabela> tabDef1,
                          vector<int> mont1,
                          vector<tabela> tabUso2,
                          vector<tabela> tabDef2,
                          vector<int> mont2){

    int corr2 = mont1.size();
    vector<int> ligFinal;

    ///CORRE��O DOS ENDERE�OS DO M�DULO 2
    //percorro o c�digo montado do m�dulo 2
    int i=0;
    while(true){
        //caso chegue at� o final do c�digo objeto
        if(i >= mont2.size())
            break;

        //caso diretiva seja COPY corrijo os tr�s pr�ximos
        if(mont2[i] == 9){
            i++; if(mont2[i]!= 0) mont2[i] = mont2[i]+corr2;
            i++; if(mont2[i]!= 0) mont2[i] = mont2[i]+corr2;
        }
        //caso seja uma diretiva stop eu paro pois n�o � necess�rio dois stops no programa
        else if(mont2[i] == 14){
            continue;
        }
        //caso seja qualquer outra diretiva pego somn
        else{
            //pego somente uma label
            i++; if(mont2[i]!= 0) mont2[i] = mont2[i]+corr2;
        }
        i++;
    }

    ///CORRE��O DA TABELA DE USO M�D 1
    //percorro a tabela de Uso do m�dulo 1
    for(int i = 0; i<tabUso1.size() ; i++){
        //percorro a tabela de defini��o 2 para encaixar as defini��es
        for(int j=0; j<tabDef2.size(); j++){
            //caso eu encontre as mesmas labels
            if(tabUso1[i].simbolo == tabDef2[j].simbolo){
                mont1[tabUso1[i].valor] = tabDef2[j].valor+corr2;
                break;
            }
        }
    }

    ///CORRE��O DA TABELA DE USO M�D 2
    //percorro a tabela de Uso do m�dulo 2
    for(int i = 0; i<tabUso2.size() ; i++){
        //percorro a tabela de defini��o 2 para encaixar as defini��es
        for(int j=0; j<tabDef1.size(); j++){
            //caso eu encontre as mesmas labels
            if(tabUso2[i].simbolo == tabDef1[j].simbolo){
                mont2[tabUso2[i].valor] = tabDef1[j].valor;
            }
        }
    }

    ligFinal.insert( ligFinal.end(), mont1.begin(), mont1.end() );
    ligFinal.insert( ligFinal.end(), mont2.begin(), mont2.end() );

    return ligFinal;
}
