#ifndef functions
#define functions

//Classes
typedef struct Tabela{
    //propriedades
    string simbolo;
    int valor;
    //funções
}tabela;

void imprimi();

//funão que retorna a tabela de uso
vector<tabela> iniciaTabUso(vector<string> arq_vector);

//função que retorna a tabela de definição
vector<tabela> iniciaTabDef(vector<string> arq_vector);

//função que retorna a pré montagem dos módulos
vector<int> iniciaTabMont(vector<string> arq_vector);

#endif // functions
