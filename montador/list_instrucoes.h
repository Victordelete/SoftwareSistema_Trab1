#ifndef LIST_INSTRUCAO_INCLUDED
#define LIST_INSTRUCAO_INCLUDED

typedef struct listInstrucao{
    char nome_inst[20];
    int operandos;
    int opcode;
    int tamanho;
}list_Instrucao;

//Função para iniciação das propriedades de instrução
void inicia_vetor_inst(list_Instrucao *vetor_inst);
//void inicia_vetor_inst(list_Instrucao vetor_inst[14]);

//função para impressão dessa lista  de instruções
void imprimi_instrucoes(list_Instrucao *vetor_inst);
#endif // LIST_INSTRUCAO_INCLUDED
