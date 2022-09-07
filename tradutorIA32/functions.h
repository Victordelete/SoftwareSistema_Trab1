#ifndef functions
#define functions

//Função recebe string com o codigo objeto e retorna vector<int> com as instruções
//e endereços.
vector<int> convertInteiro(string strCodigo);

//Função principal de interpretação da tradução
vector<string> tradutor(vector<int> vecCodigo);

#endif // functions
