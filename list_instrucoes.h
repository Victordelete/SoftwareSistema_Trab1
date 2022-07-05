#ifndef LIST_INSTRUCAO_INCLUDED
#define LIST_INSTRUCAO_INCLUDED

typedef struct listInstrucao{
    char nome_inst[20];
    int operandos;
    int opcode;
    int tamanho;
}list_Instrucao;

//Fun��o para inicia��o das propriedades de instru��o
void inicia_vetor_inst(list_Instrucao *vetor_inst);
//void inicia_vetor_inst(list_Instrucao vetor_inst[14]);

//fun��o para impress�o dessa lista  de instru��es
void imprimi_instrucoes(list_Instrucao *vetor_inst);
#endif // LIST_INSTRUCAO_INCLUDED
