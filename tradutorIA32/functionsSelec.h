#ifndef functionsSelec
#define functionsSelec

//Função análisa funções que recebem nenhum argumento STOP
vector<string> geraSemArgumento(vector<string> vecSaida, int arg1);

//Função análisa as funções assembly que recebem somente um agumento: a maioria
vector<string> geraUmArgumento(vector<string> vecSaida, int arg1, int arg2);

//Função análisa as funções assembly qye recebem 2 argumentos: COPY, SINPUT, SOUTPUT
vector<string> geraDoisArgumento(vector<string> vecSaida, int arg1,int arg2, int arg3);

//Função converte int para string com representação variável
string convIntStr(int arg);
string convIntStrLabel(int arg);

//Função para gerar secao .data
vector<string> sectionDataHandle(vector<string> vecSaida,int ind,  int arg1);

//Função para gerar secao .bss
vector<string> sectionBssHandle (vector<string> vecSaida,int ind, int arg1);

//Função para gerar seção .bss com SPACE X
vector<string> sectionBssHandleX (vector<string> vecSaida,int ind, int arg1);

//Função insere as funções desenvolvidas em x86
vector<string> insereBaseIO(void );

//Função lida com os jumps
vector<string> geraDeslocamento(vector<string> vecSaida, vector<int> vecInd, int arg1, int arg2);

#endif // functionsSelec


