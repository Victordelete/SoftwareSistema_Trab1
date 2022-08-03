//Módulo de definição das funções utilizadas no ligador

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

#include "functions.h"

//função auxiliar para impressão das tabelas criadas
void imprimi(vector<tabela> tab, string tipImpressao){
    cout << tipImpressao <<"\n";
    for(int i=0; i<tab.size(); i++){
        cout<<tab[i].simbolo <<":"<<tab[i].valor <<"\n";
    }
    cout<<"\n";
    return;
}

//função auxiliar para impressão do vector de int da montagem recebidas
void imprimiVecInt(vector<int> vecSaida, string tipImpressao){
    cout<< tipImpressao <<"\n";
    for(int i = 0 ; i<vecSaida.size(); i++){
        cout<<vecSaida[i]<<"_";
    }
    cout<<"\n\n";
    return;
}

//função que retorna a tabela de uso
 vector<tabela> iniciaTabUso(vector<string> arq_vector){
    vector<tabela> tabUso;
    tabela tabtemp;
    bool tabUsoBool = false;

    //percorro todo o vector do meu arquivo
    for(int i=0 ; i<arq_vector.size(); i++){
        //delimito qual é o inicio da minha tabela de uso
        if(arq_vector[i]== "TABELA USO"){
            tabUsoBool = true;
            continue;
        }

        if(tabUsoBool){
                if(arq_vector[i] =="\0") //saio do laço caso saia da região da tabUso
                    break;
            //coloco os dados lidos em uma variável temporária
            tabtemp.simbolo = arq_vector[i].substr(0, arq_vector[i].find(" "));
            //tabtemp.valor = arq_vector[i].substr(arq_vector[i].find(" ")+1, arq_vector[i].size());
            stringstream(arq_vector[i].substr(arq_vector[i].find(" ")+1, arq_vector[i].size()))>>tabtemp.valor;
            tabUso.push_back(tabtemp); //atualizo meu vector
        }
    }
    return tabUso;
}

//função que retorna a tabela de definição
vector<tabela> iniciaTabDef(vector<string> arq_vector){
    vector<tabela> tabDef;
    tabela tabtemp;
    bool tabDefBool = false;

    //percorro todo o vector do meu arquivo
    for(int i=0 ; i<arq_vector.size(); i++){
        //delimito qual é o inicio da minha tabela de uso
        if(arq_vector[i]== "TABELA DEF"){
            tabDefBool = true;
            continue;
        }

        if(tabDefBool){
                if(arq_vector[i] =="\0") //saio do laço caso saia da região da tabDef
                    break;
            //coloco os dados lidos em uma variável temporária
            tabtemp.simbolo = arq_vector[i].substr(0, arq_vector[i].find(" "));
            //tabtemp.valor = arq_vector[i].substr(arq_vector[i].find(" ")+1, arq_vector[i].size());
            stringstream(arq_vector[i].substr(arq_vector[i].find(" ")+1, arq_vector[i].size()))>>tabtemp.valor;
            tabDef.push_back(tabtemp); //atualizo meu vector
        }
    }
    return tabDef;
}

//função que retorna a pré montagem dos módulos
vector<int> iniciaTabMont(vector<string> arq_vector){
    //estou assumindo que o código montado está na última linah do arquivo
    string ultLinha = arq_vector[arq_vector.size()-1];
    //cout<<ultLinha<<"\n\n\n";
    int temp;
    vector<int> vecSaida;
    int ind = 0;//indices para pular os espaços

    while(true ){
        ind = ultLinha.find(" ");
            if(ind == -1){
                //cout<<"final\n";
                //caso não encontre é porque a string acabou
                    //if(ultLinha.size() == 0) //se a string for diferente de zero ela acaba e não tinha espaço no final
                      //  break;
                    //caso tivesse espaço no final eu pego o último item
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

//função que faz a ligação final das tabelas construídas
vector<int> iniciaTabMont(vector<tabela> tabUso1,
                          vector<tabela> tabDef1,
                          vector<int> mont1,
                          vector<tabela> tabUso2,
                          vector<tabela> tabDef2,
                          vector<int> mont2){

    int corr2 = mont1.size();
    vector<int> ligFinal;

    ///CORREÇÃO DOS ENDEREÇOS DO MÓDULO 2
    //percorro o código montado do módulo 2
    int i=0;
    while(true){
        //caso chegue até o final do código objeto
        if(i >= mont2.size())
            break;

        //caso diretiva seja COPY corrijo os três próximos
        if(mont2[i] == 9){
            i++; if(mont2[i]!= 0) mont2[i] = mont2[i]+corr2;
            i++; if(mont2[i]!= 0) mont2[i] = mont2[i]+corr2;
        }
        //caso seja uma diretiva stop eu paro pois não é necessário dois stops no programa
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

    ///CORREÇÃO DA TABELA DE USO MÓD 1
    //percorro a tabela de Uso do módulo 1
    for(int i = 0; i<tabUso1.size() ; i++){
        //percorro a tabela de definição 2 para encaixar as definições
        for(int j=0; j<tabDef2.size(); j++){
            //caso eu encontre as mesmas labels
            if(tabUso1[i].simbolo == tabDef2[j].simbolo){
                mont1[tabUso1[i].valor] = tabDef2[j].valor+corr2;
                break;
            }
        }
    }

    ///CORREÇÃO DA TABELA DE USO MÓD 2
    //percorro a tabela de Uso do módulo 2
    for(int i = 0; i<tabUso2.size() ; i++){
        //percorro a tabela de definição 2 para encaixar as definições
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
