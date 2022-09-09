#ifndef functionsSelec
#define functionsSelec

//Fun��o an�lisa fun��es que recebem nenhum argumento STOP
vector<string> geraSemArgumento(vector<string> vecSaida, int arg1);

//Fun��o an�lisa as fun��es assembly que recebem somente um agumento: a maioria
vector<string> geraUmArgumento(vector<string> vecSaida, int arg1, int arg2);

//Fun��o an�lisa as fun��es assembly qye recebem 2 argumentos: COPY, SINPUT, SOUTPUT
vector<string> geraDoisArgumento(vector<string> vecSaida, int arg1,int arg2, int arg3);

//Fun��o converte int para string com representa��o vari�vel
string convIntStr(int arg);

//Fun��o para gerar secao .data
vector<string> sectionDataHandle(vector<string> vecSaida,int ind,  int arg1);

//Fun��o para gerar secao .bss
vector<string> sectionBssHandle (vector<string> vecSaida,int ind, int arg1);

#endif // functionsSelec


