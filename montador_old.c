#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//tipo de armazenagem para arquivo de processamento
//arquivo todo guardado em memória. Alto gasto de memória porém mais rápido
struct type_line_inst{
int num_linha;
char string_linha[50] ; //numero máximo de caracteres por linha - limita o nome dos rótulos por tamanho
struct type_line_inst *prox;
char termo1[20];
char termo2[20];
char termo3[20];

int opcode;

int endereco;
};

struct Equi_Def{
    int linha;
    char label[20];
    int valor;
    int estado;
    int endereco;
    struct Equi_Def *prox;
};

//struct para o vetor com informçaão das instruções
struct nome_instrucoes {
    char nome_inst[20];
    int operandos;
    int opcode;
    int tamanho;
};

//variavel global para o fim da lista de equivalencias
struct Equi_Def *TabEq_fin;

//vetor de informação de instruções
struct nome_instrucoes vetor_inst[15];

//função inicia dados de instruções
void inicia_vetor_inst();

int taman_memo;

///FUNÇÕES AUXILIARES
/*////////////////////////////////////*/

//insere na lista de instruções
struct type_line_inst *insere_lista_inst (int i, char *string_instrucao, struct type_line_inst * pont_fin){
    struct type_line_inst *nova_inst;
    //novo item da lista
    nova_inst = malloc(sizeof(struct type_line_inst));
    //os valores do novo termo da lista
    nova_inst->num_linha = i;
    nova_inst->endereco = 0;
    nova_inst->opcode = -1;
    strcpy (nova_inst->string_linha  , string_instrucao);
    nova_inst->termo1[0]='\0';
    nova_inst->termo2[0]='\0';
    nova_inst->termo3[0]='\0';

    //imprimindo para testes iniciais
    //printf("%d %s",nova_inst->num_linha, nova_inst->string_linha);
    //realoco o ultimo elemento da lista para este novo
    pont_fin->prox = nova_inst;
    nova_inst->prox = NULL; //colocando NULL no final do arquivo para indicar final
    return nova_inst;

}

//insere na lista de definições
struct Equi_Def *insere_lista_equi(int num_linha, char *termo1, char *termo3, struct Equi_Def *TabEq_fin, int estado, int endereco){
    struct Equi_Def *nova_def;
    nova_def = malloc(sizeof(struct Equi_Def));

    //redefinindo os valores na lista
    strcpy(nova_def->label,termo1);
    nova_def->valor = atoi(termo3);
    nova_def->estado = estado;
    nova_def->endereco = endereco;
    nova_def->linha = num_linha;
    nova_def->prox = NULL;

    ///printf("equi: %s %d\n", nova_def->label, nova_def->valor);

    TabEq_fin->prox = nova_def;

    return nova_def;
}

//procura uma label na lista de definições. Utilizado também na primeira passagem para ver como esta
int procura_def(struct Equi_Def  *TabEq_ini, char *label_do_if){
    //variavel para modificar a string tirar dois pontos
    char varial[30];

    while(TabEq_ini != NULL){
        strcpy(varial,TabEq_ini->label);
        //tiro o dois pontos para comparação
        varial[strlen(varial)-1] = '\0';
        if(stricmp(varial, label_do_if)==0){
            return TabEq_ini->valor;
        }

    TabEq_ini=TabEq_ini->prox;
    }

    return -9999;
}

//Exclui instrução da lista de instruções
struct type_line_inst *exclui(struct type_line_inst *pont_ant, struct type_line_inst *pont_exl){ //função para excluir recebe o anterior e o que é para excluir
    struct type_line_inst *pont_temp;

    //caso seja para excluir o primeiro termo
    ///if(pont_ant == pont_exl){
    if(pont_ant == NULL){
        ///printf("caso1\n");
        pont_temp = pont_exl->prox;
        free(pont_exl);
        free(pont_ant);
        return pont_temp;
    }
    if(pont_exl->prox == NULL){
        ///printf("caso2\n");
        pont_ant->prox = NULL;
        free(pont_exl);
        return pont_ant;
    }
    else{//excluir no meio da lista
        ///printf("caso3\n");
        pont_ant->prox = pont_exl->prox;
        free(pont_exl);
        return pont_ant;
    }

}

//procura pra ver se o rótulo existe
int analisa_rotulo(struct Equi_Def * ini_TabEq, char *rotulo){
    while(ini_TabEq!=NULL){
        if(strcmp(ini_TabEq->label, rotulo)== 0){
            printf("Teste de retorno de analisa rotulo\n");
            return 1; ///erro label já existia
        }
        ini_TabEq = ini_TabEq->prox;
    }

    //retornar zero caso nao encontre na lista o rotulo
    return 0;
}

//procuro a posição de um label especifico
struct Equi_Def* ProcuraEquivalencia(struct Equi_Def* TabEq_ini, char* label){
    char varial[30];

    while(TabEq_ini!=NULL){
        strcpy(varial, TabEq_ini->label);
        //retiro o dois pontos
        varial[strlen(varial)-1] = '\0';

        if(strcmp(varial, label)==0){
            return TabEq_ini;
        }

        TabEq_ini = TabEq_ini->prox;
    }
    return NULL;
}

//Função de base para imprimir na tela - Utilizado somente para desenvolvimento
void imprimi(struct type_line_inst *pont_ini){
    while(pont_ini != NULL){
        printf("end: %d -opcode %d - %s",  pont_ini->endereco, pont_ini->opcode, pont_ini->string_linha);
        ///printf("termos:%s %s %s\n", pont_ini->termo1, pont_ini->termo2, pont_ini->termo3);
        pont_ini = pont_ini->prox;
    }

    //printf("Impresso com sucesso.\n\n");
    return ;
}

//imprimi em um arquivo de saída a compilagem construída
void imprimi_arquivo(char *nome_arq_an, char tipo_mont, struct type_line_inst *pont_ini, int *vetor_mem){
    //avaliando o nome correto do arquivo
    int i = 4;
    ///taman_memo variavel global para utilização da memoria criada;

    char nome_arq[50];

    strcpy(nome_arq, nome_arq_an);

    if(tipo_mont == 'p'){
        char *prefixo_p = ".pre";

        for(i=0; i<4; i++){
            nome_arq[strlen(nome_arq) - 4 +i] = prefixo_p[i];
        }
        FILE *arquivo_pre;
        arquivo_pre = fopen(nome_arq, "w+"); //abro arquivo com nome criado ou crio um novo caso
        //testa a criação do arquivo
        if(arquivo_pre == NULL){
            printf("ERRO -> Falha na abertura do arquivo pre.\n");
        }
        //imprimo no arquivo gerado
        while(pont_ini != NULL){
        fprintf(arquivo_pre,"%s", pont_ini->string_linha);
        pont_ini = pont_ini->prox;
        }
    fclose(arquivo_pre);
    }

    if(tipo_mont == 'o'){
        char *prefixo_p = ".obj";
        int i = 0;

        for(i=0; i<4; i++){
            nome_arq[strlen(nome_arq) - 4 +i] = prefixo_p[i];
        }
        FILE *arquivo_obj;
        arquivo_obj = fopen(nome_arq, "w+"); //abro arquivo com nome criado ou crio um novo caso
        //testa a criação do arquivo
        if(arquivo_obj == NULL){
            printf("ERRO -> Falha na criação do arquivo obj.\n");
        }
        //imprimo no arquivo gerado
        for(i=0; i<taman_memo; i++){
            fprintf(arquivo_obj,"%d ",vetor_mem[i] );
        }

    fclose(arquivo_obj);
    }

    return ;
}

///FUNÇÕES DE PROCESSAMENTO
/*////////////////////////////////////*/

//preprocessamento acontece na lista de instruções iniciais.
struct type_line_inst * pre_processamento( struct type_line_inst *pont_ini, struct Equi_Def *TabEq_ini){
    //novo ponteiro para conseguir voltar ao inicio caso precise
    struct type_line_inst *ini_b;
    struct type_line_inst *pont_ant;
        ini_b = pont_ini;
        pont_ant = pont_ini;
    //struct Equi_Def *TabEq_fin;
        TabEq_fin = TabEq_ini;

    char varial[20];

    int i_b = 0;
    int i = 0;
    int ind = 0;
    int ind_term = 0;
    int t1, t2, t3;

    int Pre_Erro = 0;

    while (ini_b != NULL ){
        i=0;

        ///avaliando comentário e linhas vazias
        for(i = 0; i <= strlen(ini_b->string_linha); i++){ //percorro toda a string da instrução
            //caso encontre um comentário
            if( ini_b->string_linha[i] == ';'){
                    if(i == 0){//caso seja um comentário no inicio tbm excluo a linha
                        //printf("exclui 2\n");
                        ini_b = exclui(pont_ant, ini_b);
                            if(pont_ant == NULL){//caso exclua o primeiro termo
                                pont_ini = ini_b;
                            }
                        break;
                    }
                ini_b->string_linha[i] = '\n';
                ini_b->string_linha[i+1] = '\0';
                break;
                }

            //caso encontre uma linha vazia retiro ela
            if( strlen(ini_b->string_linha) == 1 ){
                    ini_b = exclui(pont_ant, ini_b);
                    if(pont_ant == NULL){//caso exclua o primeiro termo
                        pont_ini = ini_b;
                    }
                    break;
            }
        }

        strcpy(varial,ini_b->string_linha);
        i=0;
        i_b=0;
        ///avaliando os espaços extras
        for(i=0; i<strlen(varial); i++){
            if(varial[i]== ' '){
                ind = 0;
                continue;
            }
            else{
                ini_b->string_linha[i_b] = varial[i];
                i_b++;

                if(varial[i+1] == ' '){
                    ini_b->string_linha[i_b]= ' ';
                    i_b++;
                }
            }
        }

        ini_b->string_linha[i_b] = '\0';
        ind = 0;
        ind_term = 1;
        t1 =0;
        t2 =0;
        t3 =0;
        strcpy(varial,ini_b->string_linha) ;
        ///atribuindo os termos a partir da string nova
        for(i=0; i<strlen(varial) ; i++){
            if(varial[i] == ' ' || varial[i] == '\n' || varial[i] == '\0'){
                ind =0;
                ind_term++;
            }
            if(ind_term == 1 && varial[i] != ' ' && varial[i] != '\n' && varial[i] != '\0'){
                ini_b->termo1[ind] = varial[i];
                ind++;
                t1++;
            }
            if(ind_term == 2 && varial[i] != ' ' && varial[i] != '\n' && varial[i] != '\0'){
                ini_b->termo2[ind] = varial[i];
                ind++;
                t2++;
            }
            if(ind_term == 3 && varial[i] != ' ' && varial[i] != '\n' && varial[i] != '\0'){
                ini_b->termo3[ind] = varial[i];
                ind++;
                t3++;
            }
        }

        //definição de fim de string para as string reconhecidas
        ini_b->termo1[t1] = '\0';
        ini_b->termo2[t2] = '\0';
        ini_b->termo3[t3] = '\0';

        //andando com o ponteiro
        pont_ant = ini_b;
        ini_b = ini_b->prox ;
    }

    ini_b = pont_ini;
    pont_ant = NULL;

    i = 1; //vou usar uma variável anterior para limitar caso deseje exlcui uma linha naterior
    ind = 0;

    int Marca_section_text = 0;
    int  Marca_section_data  = 0;

    while(ini_b != NULL){
        //preciso encontrar minha section text
        if(strcmp(ini_b->termo1, "SECTION") == 0 &&  strcmp(ini_b->termo2, "TEXT") == 0){
           Marca_section_text = 1;
        }
        if(strcmp(ini_b->termo1, "SECTION")== 0 &&  strcmp(ini_b->termo2, "DATA" ) == 0){
            Marca_section_data  = 1;
            Marca_section_text = 2; //caso de so haver data
        }

            //caso que preciso excluir a linha seguinte
            if(i == 0){
                ///printf("excluindo o proximo da lista de instrucoes.\n");
                ini_b = exclui(pont_ant, ini_b);
                    if(pont_ant == NULL){//caso exclua o primeiro termo
                        pont_ini = ini_b;
                    }
                i = 1;
                continue;
            }
        //caso haja uma equivalência eu defino a equivalência na lista e excluo a linha
        if(strcmp(ini_b->termo2, "EQU") == 0){
                if(Marca_section_text == 1 || Marca_section_data == 1){
                    printf("ERRO->Linha %d: EQU nao permitido em SECTION TEXT.\n", ini_b->num_linha);
                    Pre_Erro = 1;
                }
            TabEq_fin = insere_lista_equi(ini_b->num_linha, ini_b->termo1, ini_b->termo3, TabEq_fin, 1, -1);
            ini_b = exclui(pont_ant, ini_b);
                if(pont_ant == NULL){//caso exclua o primeiro termo
                    pont_ini = ini_b;
                }
            continue;
        }

        if(strcmp(ini_b->termo1, "IF") == 0){
            //procuro a minha definição na lista de definições
            ind = procura_def(TabEq_ini, ini_b->termo2);

            if( ind != 1 && ind != -9999){ //indice utilizado para descrever erro
                //então eu excluo a próxima linah setando i
                i = 0;
            }
            if( ind == -9999){
                printf("ERRO->Linha %d: label de EQU ' %s ' nao definido.\n", ini_b->num_linha, ini_b->termo2);
                Pre_Erro = 1;
            }

            ini_b = exclui(pont_ant, ini_b);
                if(pont_ant == NULL){//caso exclua o primeiro termo
                    pont_ini = ini_b;
                }
        }

        pont_ant = ini_b;
        ini_b=ini_b->prox;
    }

    //caso o programa não encontre as seções básicas necessárias
    if(Marca_section_data == 0 || Marca_section_text == 0){
        printf("ERRO-> Necessario a presenca de SECTION TEXT e SECTION DATA no programa.\n");
        Pre_Erro = 1;
    }

    //caso tenha algum erro no preprocessamento eu apago a minha lista
    if(Pre_Erro == 1){
        pont_ini = NULL;
    }

    return pont_ini;
}

//primeira passagem do algoritmo
struct type_line_inst* pri_passagem(struct type_line_inst *pont_ini, struct Equi_Def *TabEq_ini){

    struct type_line_inst* ini_b;
        ini_b = pont_ini; //novo ponteiro inicial para não perder a referência

    struct Equi_Def *ini_TabEq;
        ini_TabEq = TabEq_ini; // novo ponteiro para lista de

    ///TabEq_fin;  é a tabela para o final de referências

    //inicio o vetor de instruções, mesmo sendo uma variável global
    inicia_vetor_inst();
        ///vetor de dados de instruções em Vetor_inst;
    //percorro toda a lista de instruções pre processadas

    int ind = -1;
    int i = 0;
    char varial[50]; //uso variado

    int Marcador_varial = 0;

    int Marca_Section_Text =0;
    int Marca_Section_Data =0;

    int Marca_de_Erro = 0;

    int ender_geral = 0;


    while(ini_b!=NULL){
        ind = -1;
        Marcador_varial = 0;
        ///strcmp(ini_b->termo1, "SECTION") == 0 &&  strcmp(ini_b->termo2, "TEXT") == 0){
            //caso tenha somente as definições de SECTION como já foram análisadas eu pulo
            if(strcmp(ini_b->termo1,"SECTION") == 0 && strcmp(ini_b->termo2, "TEXT")== 0){
                ini_b = ini_b->prox;
                Marca_Section_Text = 1;
                continue;
            }

            if(strcmp(ini_b->termo1,"SECTION") == 0 && strcmp(ini_b->termo2, "DATA")==0){
                ini_b = ini_b->prox;
                Marca_Section_Data =1;
                Marca_Section_Text =2;
                continue;
            }

        if(Marca_Section_Text == 1){
            //procuro minha instrução atual no vetor de instruções
            for(i=0; i<14; i++){
                if(strcmp(vetor_inst[i].nome_inst, ini_b->termo1) == 0){
                    ind = i;
                    ini_b->endereco = ender_geral;
                    ini_b->opcode = vetor_inst[ind].opcode;
                    ender_geral = ender_geral + vetor_inst[ind].tamanho ;
                    break;
                }
            }
                //caso não tenha encontrado a instrução na lista eu averiguo se é um label
                if(ind == -1 &&  ini_b->termo1[strlen(ini_b->termo1)-1] == ':' ){
                    //teste se o rótulo começa com numero
                        i = ini_b->termo1[0] - '0';
                        if(i>=0 && i<=9){
                            printf("ERRO -> Linha %d: nao permitido rotulo '%s' iniciado com numero\n", ini_b->num_linha, ini_b->termo1);
                            ini_b = ini_b->prox;
                            continue;
                        }//assumindo quebra de linha no rótulo

                    //analisar para ver se rotulo já existe
                        if(analisa_rotulo(ini_TabEq, ini_b->termo1 ) == 1){
                            printf("ERRO -> Linha %d: rotulo '%s' repetido.\n", ini_b->num_linha, ini_b->termo1);
                            Marca_de_Erro = 1;
                            ini_b=ini_b->prox;
                            continue;
                        }
                    //caso nao exista eu acrescento o rotulo a lista
                    TabEq_fin = insere_lista_equi(ini_b->num_linha, ini_b->termo1, ini_b->termo3, TabEq_fin, 1, ender_geral);
                    ini_b = ini_b->prox;
                    ender_geral++;
                    continue;
                    //associando o rotulo a linha
                }

                //caso nao encontre o operando
                if(ind == -1){
                    printf("ERRO -> Linha %d: operando '%s' nao reconhecido.\n", ini_b->num_linha, ini_b->termo1);
                    ini_b = ini_b->prox;
                    Marca_de_Erro = 1;
                    continue;
                }
            //análise sintatica para numero de termos
            if(ini_b->termo2[0] != '\0'){
                Marcador_varial ++;
            }

            //caso haja dois termos na instrução análisada
            if(strlen(ini_b->termo3) != 0){
                Marcador_varial ++;
            }

            if(Marcador_varial  != vetor_inst[ind].operandos){ //caso tenha diferentes numeros de termos
                printf("ERRO -> Linha %d: quantidade de termos incorreta.\n", ini_b->num_linha);
                Marca_de_Erro = 1;
            }
        }

        //na seção de data eu quero que tudo seja definição de variável
        if(Marca_Section_Data == 1){
            ini_TabEq = TabEq_ini;

                if(ini_b->termo1[strlen(ini_b->termo1)-1] != ':'){
                    printf("ERRO -> Linha %d: declaracoes de dados devem conter ':'\n", ini_b->num_linha);
                    Marca_de_Erro = 1;
                    ini_b = ini_b->prox;
                    continue;
                }

            while(ini_TabEq != NULL){
                strcpy(varial, ini_b->termo1);
                varial[strlen(varial)-1] = '\0'; //tiro o dois pontos para comparação com a utilização das label

                //caso ache a minha label na lista de labels
                if(strcmp(varial, ini_TabEq->label)==0){
                    ini_TabEq->endereco = ender_geral;
                        ender_geral = ender_geral + 1;
                    ini_TabEq->estado = 1; //seto meu estado como verdadeiro
                    ini_TabEq->valor = 0; //setor respaw como zero.

                    //ini_b = ini_b->prox;
                    break;
                }

                ini_TabEq = ini_TabEq->prox;
            }

            //caso não ache no na lista eu posso acrescentar na lista
            //em SPACE eu adiciono espaço vazio
            if(strcmp(ini_b->termo2, "SPACE")==0){
                //adiciono o novo item
                TabEq_fin = insere_lista_equi(ini_b->num_linha, ini_b->termo1, ini_b->termo3, TabEq_fin, 1, ender_geral);
                ender_geral = ender_geral + 1;
            }

            //em CONST eu adiciono OO
            if(strcmp(ini_b->termo2, "CONST")==0){
                    //caso encontre diretiva const mas não encontre um valor de rescignificação
                    if(strlen(ini_b->termo3) == 0){
                        printf("ERRO -> Linha %d: diretiva 'CONST' deve conter valor associado.\n", ini_b->num_linha);
                        Marca_de_Erro = 1;
                        ini_b = ini_b->prox;
                        continue;
                    }
                //adiciono o novo item
                TabEq_fin = insere_lista_equi(ini_b->num_linha, ini_b->termo1, ini_b->termo3, TabEq_fin, 1, ender_geral);
                ender_geral = ender_geral + 1;
            }
        }

        ini_b = ini_b->prox;
    }
    ini_TabEq = TabEq_ini;
    //uso o primeiro item extra da lista de equivalências para passar a quantidade em memória
    taman_memo = ender_geral;

    ini_TabEq = TabEq_ini;

    return pont_ini;
}

//segunda passagem do meu algoritmo
struct type_line_inst * seg_passagem( struct type_line_inst *pont_ini, struct Equi_Def *TabEq_ini, int *vetor_mem){
    struct type_line_inst* ini_b;
        ini_b = pont_ini; //novo ponteiro inicial para não perder a referência

    struct Equi_Def *ini_TabEq;
        ini_TabEq = TabEq_ini; // novo ponteiro para lista de

    //vetor com tamanho da memoria final
    int i = 0;
    int Marca_erro = 0;

    int Marca_section_data = 0;
    int Marca_section_text = 0;
        for(i=0; i<taman_memo; i++ ){
            vetor_mem[i] = -1;
        }

    i=0;

    while(ini_b!=NULL){
        ini_TabEq = TabEq_ini;

        if(strcmp(ini_b->termo1,"SECTION") == 0 && strcmp(ini_b->termo2, "DATA")==0){
            ini_b = ini_b->prox;
            Marca_section_data =1;
            Marca_section_text = 0;
            continue;
        }

        if(strcmp(ini_b->termo1,"SECTION") == 0 && strcmp(ini_b->termo2, "TEXT")==0){
            Marca_section_text = 1;
            ini_b = ini_b->prox;
            continue;
        }

        if(Marca_section_text == 1){
            //vejo se nao é um rótulo porque não quis excluir a linha na primeira passagem
            if(ini_b->termo1[strlen(ini_b->termo1)-1] == ':' && Marca_section_data == 0){
                ini_b = ini_b->prox;
                continue;
            }
            else{
                //adiciono em memória o opcode
                vetor_mem[i] = ini_b->opcode;
                i++;
                    if(strlen(ini_b->termo2)!= 0){
                        //procuro na lista de pendências
                        ini_TabEq = ProcuraEquivalencia(ini_TabEq, ini_b->termo2);

                            //erro de rotulo nao definido
                            if(ini_TabEq == NULL){
                                printf("ERRO -> Linha %d: label '%s' nao definida.\n", ini_b->num_linha, ini_b->termo2);
                                Marca_erro = 1;
                                ini_b = ini_b->prox;
                                continue;
                            };
                        vetor_mem[i] = ini_TabEq->endereco;

                        i++;

                        ini_b=ini_b->prox;
                        continue;
                    }

                    if(strlen(ini_b->termo3)!= 0){;
                        //procuro na lista de pendências
                        ini_TabEq = ProcuraEquivalencia(ini_TabEq, ini_b->termo2);
                            if(ini_TabEq == NULL){
                                printf("ERRO -> Linha %d: label '%s' nao definida.\n", ini_b->num_linha, ini_b->termo3);
                                Marca_erro = 1;
                                ini_b = ini_b->prox;
                                continue;
                            }
                        vetor_mem[i] = ini_TabEq->endereco;
                        i++;
                    }

                }
        }
        if(Marca_section_data == 1){
                while(ini_TabEq!=0){
                        if(strcmp(ini_b->termo1, ini_TabEq->label)== 0){
                            vetor_mem[i] = ini_TabEq->valor;
                            i++;
                            break;
                        }
                    ini_TabEq = ini_TabEq->prox;
                }
        }
        ini_b=ini_b->prox;
    }

    if(Marca_erro != 0){
        vetor_mem[0] = -1;
    }
    return pont_ini;
}

//função principal
///int main(char* nome_arquivo, char tipo_abert){
int main(void){
    //nome do arquivo a ser compilado mudar depois
char nome_arquivo[] = "arquivo.txt";
    //tipo de abertura - setar depois
char tipo_abert = 'p';

    // ponteiro para arquivo onde ficará o arquivo base
    FILE *arq_mont;

    // o nome do arquivo futuramente deverá vir da chamada do programa
    arq_mont = fopen(nome_arquivo, "r"); //////////LEMBRAR DE RETIRAR ESSA CHAMADA

    //testando se o arquivo foi realmente criado
    if(arq_mont == NULL){
        printf("Erro na abertura do arquivo!\n");
        return -1;
    }

    //variavel onde ficará o primeiro termo da lista de instruções internas
    struct type_line_inst lista_instrucao;
    //ponteiro para elementos estrategicos da lista
    struct type_line_inst *pont_ini; //ponteiro inicio
    struct type_line_inst *pont_fin; //ponteiro final

    //lista inicialmente com um único termo
        pont_ini = &lista_instrucao;
        pont_fin = &lista_instrucao;

    //equivalencias utilizadas para o preprocessamento
    struct Equi_Def TabelaEquivalencia;
    //ponteiro para essa lista
    struct Equi_Def *TabEq_ini;
        TabEq_ini = &TabelaEquivalencia;
        TabEq_ini->estado=0;
        TabEq_ini->linha=-1;
        TabEq_ini->prox=NULL;
        TabEq_ini->valor=0;
        strcpy(TabEq_ini->label,"INICIO_LISTA_EQUIVALENCIA");

        TabEq_fin = TabEq_ini;
    //string para testes
    char texto_str[50];
    //variavel para controle do tamanho
    int i = 1;
    //criando lista
        //criando primeiro elemento
        fgets(texto_str, 50, arq_mont);
        pont_ini->num_linha = 1; i++;
        strcpy (pont_ini->string_linha , texto_str);

    while(fgets(texto_str, 50, arq_mont) != NULL){
        //insere no final da lista a linha no arquivo original e a string a ser guardada
        pont_fin = insere_lista_inst(i, texto_str, pont_fin);
            i=i+1;
        }

    // fechando arquivo
    fclose(arq_mont);

    //onde guardo vetor de memoria
    int *pont_vetor;

    ///CASO TENHA SOMENTE PRÉ PROCESSAMENTO
    if(tipo_abert == 'p'){
        pont_ini = pre_processamento(pont_ini, TabEq_ini);
            if(pont_ini == NULL){ //houve erro no preprocessamento
                printf("Arquivo de pre-processamento nao criado.\n");
                return -1;
            }
        imprimi_arquivo(nome_arquivo, tipo_abert, pont_ini, pont_vetor);
        imprimi(pont_ini);
        printf("Arquivo preprocessado com sucesso.\n");
        return 0;
    }

    if(tipo_abert == 'o'){
        //PREPROCESSAMENTO
        pont_ini = pre_processamento(pont_ini, TabEq_ini);
            if(pont_ini == NULL){ //houve erro no preprocessamento
                printf("Erro encontrado no preprocessamento.\n");
                return -1;
            }

        //PRIMEIRA PASSAGEM
        pont_ini = pri_passagem(pont_ini, TabEq_ini);
            if(pont_ini == NULL){ //houve erro no preprocessamento
                printf("Erro encontrado na primeira passagem.\n");
                return -1;
            }

            if(taman_memo == 0){
                printf("Erro interno nao identificado\n");
                return -1;
            }
        int vetor_mem[taman_memo];
        pont_ini = seg_passagem(pont_ini, TabEq_ini, vetor_mem);

        //segunda passagem nas instruções
            if(vetor_mem[0] == -1){ //houve erro no preprocessamento
                printf("Erro encontrado na segunda passagem.\n");
                return -1;
            }

        imprimi_arquivo(nome_arquivo, tipo_abert, pont_ini, vetor_mem);
        printf("Arquivo montado com sucesso.\n");
    }

    return(0);
}

//setando os valores do vetor de instruções
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
