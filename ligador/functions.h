#ifndef functions
#define functions

//Classes
typedef struct Tabela{
    //propriedades
    string simbolo;
    int valor;
}tabela;

//fun��o que imprime as tabelas
void imprimi(vector<tabela> tab, string tipImpressao);
void imprimiVecInt(vector<int> vecSaida, string tipImpressao);

//fun�o que retorna a tabela de uso
vector<tabela> iniciaTabUso(vector<string> arq_vector);

//fun��o que retorna a tabela de defini��o
vector<tabela> iniciaTabDef(vector<string> arq_vector);

//fun��o que retorna a pr� montagem dos m�dulos
vector<int> iniciaTabMont(vector<string> arq_vector);

//fun��o que faz a liga��o final das tabelas constru�das
vector<int> iniciaTabMont(vector<tabela> tabUso1,
                          vector<tabela> tabDef1,
                          vector<int> mont1,
                          vector<tabela> tabUso2,
                          vector<tabela> tabDef2,
                          vector<int> mont2
                          );

#endif // functions
