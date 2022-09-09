#ifndef functions
#define functions


//Inicia o vetor de resultado para a tradu��o
vector<string> iniciaVector(vector<string> vecSaida);

//Fun��o imprimi todas as linhas de um vector<string>
void imprimiVecStr(vector<string> vecSaida);

//Fun��o recebe string com o codigo objeto e retorna vector<int> com as instru��es
//e endere�os.
vector<int> convertInteiro(string strCodigo);

//Fun��o principal de interpreta��o da tradu��o
vector<string> tradutor(vector<int> vecCodigo);

#endif // functions


