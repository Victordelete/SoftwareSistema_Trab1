#ifndef functions
#define functions


//Inicia o vetor de resultado para a tradução
vector<string> iniciaVector(vector<string> vecSaida);

//Função imprimi todas as linhas de um vector<string>
void imprimiVecStr(vector<string> vecSaida);

//Função recebe string com o codigo objeto e retorna vector<int> com as instruções
//e endereços.
vector<int> convertInteiro(string strCodigo);

//Função principal de interpretação da tradução
vector<string> tradutor(vector<int> vecCodigo);

#endif // functions


