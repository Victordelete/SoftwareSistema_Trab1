///setando os valores do vetor de instruções
///Iniciando vetor com opcodes/instruções
//struct para o vetor com informçaão das instruções

void inicia_vetor_inst(){
    //valores a serem colocados no vetor
    strcpy(vetor_inst[0].nome_inst, "ADD");
        vetor_inst[0].operandos = 1;
        vetor_inst[0].opcode = 1;
        vetor_inst[0].tamanho = 2;
    strcpy(vetor_inst[1].nome_inst, "SUB");
        vetor_inst[1].operandos = 1;
        vetor_inst[1].opcode = 2;
        vetor_inst[1].tamanho = 2;
    strcpy(vetor_inst[2].nome_inst, "MULT");
        vetor_inst[2].operandos = 1;
        vetor_inst[2].opcode = 3;
        vetor_inst[2].tamanho = 2;
    strcpy(vetor_inst[3].nome_inst, "DIV");
        vetor_inst[3].operandos = 1;
        vetor_inst[3].opcode = 4;
        vetor_inst[3].tamanho = 2;
    strcpy(vetor_inst[4].nome_inst, "JMP");
        vetor_inst[4].operandos = 1;
        vetor_inst[4].opcode = 5;
        vetor_inst[4].tamanho = 2;
    strcpy(vetor_inst[5].nome_inst, "JMPN");
        vetor_inst[5].operandos = 1;
        vetor_inst[5].opcode = 6;
        vetor_inst[5].tamanho = 2;
    strcpy(vetor_inst[6].nome_inst, "JMPP");
        vetor_inst[6].operandos = 1;
        vetor_inst[6].opcode = 7;
        vetor_inst[6].tamanho = 2;
    strcpy(vetor_inst[7].nome_inst, "JMPZ");
        vetor_inst[7].operandos = 1;
        vetor_inst[7].opcode = 8;
        vetor_inst[7].tamanho = 2;
    strcpy(vetor_inst[8].nome_inst, "COPY");
        vetor_inst[8].operandos = 2;
        vetor_inst[8].opcode = 9;
        vetor_inst[8].tamanho = 3;
    strcpy(vetor_inst[9].nome_inst, "LOAD");
        vetor_inst[9].operandos = 1;
        vetor_inst[9].opcode = 10;
        vetor_inst[9].tamanho = 2;
    strcpy(vetor_inst[10].nome_inst, "STORE");
        vetor_inst[10].operandos = 1;
        vetor_inst[10].opcode = 11;
        vetor_inst[10].tamanho = 2;
    strcpy(vetor_inst[11].nome_inst, "INPUT");
        vetor_inst[11].operandos = 1;
        vetor_inst[11].opcode = 12;
        vetor_inst[11].tamanho = 2;
    strcpy(vetor_inst[12].nome_inst, "OUTPUT");
        vetor_inst[12].operandos = 1;
        vetor_inst[12].opcode = 13;
        vetor_inst[12].tamanho = 2;
    strcpy(vetor_inst[13].nome_inst, "STOP"); //DIRETIVA TRATADA NA PRIMEIRA PASSAGEM
        vetor_inst[13].operandos = 0;
        vetor_inst[13].opcode = 14;
        vetor_inst[13].tamanho = 1;
}

