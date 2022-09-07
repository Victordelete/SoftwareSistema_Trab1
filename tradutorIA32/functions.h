#ifndef functions
#define functions

//Classes
typedef struct Tabela{
    //propriedades
    string simbolo;
    int valor;
}tabela;

//função que imprime as tabelas
void imprimi(vector<tabela> tab, string tipImpressao);
void imprimiVecInt(vector<int> vecSaida, string tipImpressao);

//funão que retorna a tabela de uso
vector<tabela> iniciaTabUso(vector<string> arq_vector);

//função que retorna a tabela de definição
vector<tabela> iniciaTabDef(vector<string> arq_vector);

//função que retorna a pré montagem dos módulos
vector<int> iniciaTabMont(vector<string> arq_vector);

//função que faz a ligação final das tabelas construídas
vector<int> iniciaTabMont(vector<tabela> tabUso1,
                          vector<tabela> tabDef1,
                          vector<int> mont1,
                          vector<tabela> tabUso2,
                          vector<tabela> tabDef2,
                          vector<int> mont2
                          );

#endif // functions
