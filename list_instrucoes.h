#ifndef LIST_INSTRUCAO_INCLUDED
#define LIST_INSTRUCAO_INCLUDED

typedef struct listInstrucao{
    char nome_inst[20];
    int operandos;
    int opcode;
    int tamanho;
}list_Instrucao;

void inicia_vetor_inst(list_Instrucao *vetor_inst);
//void inicia_vetor_inst(list_Instrucao vetor_inst[15]);

void imprimi_teste();
#endif // LIST_INSTRUCAO_INCLUDED
