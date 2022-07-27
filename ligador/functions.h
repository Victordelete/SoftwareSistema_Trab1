#ifndef functions
#define functions

//Classes
typedef struct Tabela{
    //propriedades
    string simbolo;
    int valor;
    //fun��es
}tabela;

void imprimi();

//fun�o que retorna a tabela de uso
vector<tabela> iniciaTabUso(vector<string> arq_vector);

//fun��o que retorna a tabela de defini��o
vector<tabela> iniciaTabDef(vector<string> arq_vector);

//fun��o que retorna a pr� montagem dos m�dulos
vector<int> iniciaTabMont(vector<string> arq_vector);

#endif // functions
