#include "imports.h"
// recebe um ponteiro para uma lista de alunos (ouseja um ponteiro para pAlunos), cria um header e acossia-o a lista ligada
int inicializa_lista_de_alunos(pAlunos* lista_de_alunos){
    pAlunos temp=(pAlunos) malloc(sizeof(noAluno));
    if(temp==NULL){ return 1; }
    temp->proximo=NULL;
    *lista_de_alunos = temp;
    return 0;
}

//aloca memoria para um vetor de dimenção 26 (tamanho do alfabeto), de structs pAlunos que irão conter as listas para cada letra acossiada a um index
int criar_tabela(pAlunos** tabela){
    *tabela= (pAlunos*) malloc(sizeof(pAlunos)*26);
    if(*tabela==NULL){ return 1; }
    for (int i = 0; i < 26; ++i) {
        if(inicializa_lista_de_alunos(*tabela+i)==1)
            return 1;
    }
    return 0;
}

// verifica se a lista esta vazia
int verifica_lista_de_alunoVazia(pAlunos lista_de_aluno){
    if(lista_de_aluno->proximo==NULL)
        return 1;
    return 0;
}

// destroi uma lista de alunos e todas as listas de despesas acossiadas (usando a função "destroi_lista_de_despesas") de forma a preservar memoria que pode assim voltar a ser usada;
pAlunos destroi_lista_de_alunos(pAlunos lista){
    pAlunos temp;
    while (!verifica_lista_de_alunoVazia(lista)){
        temp=lista;
        destroi_lista_de_despesas(temp->ficha_aluno.lista_De_Despesas);
        lista=lista->proximo;
        free(temp);
    }
    free(lista);
    return NULL;
}

// usa a função "destroi_lista_de_alunos" para destroi todas as listas acossiadas a tabela e destroi o vetor ou tabela premitindo a reutilização da memoria
void destroi_tabela(pAlunos* tabela){
    for (int i = 26; i < 0; --i) {
        tabela[i]= destroi_lista_de_alunos(tabela[i]);
        free(tabela+i);
    }
}

// recebe o possivel nome do aluno e retorna com base no primeiro caracter do nome qual a posição da lista em que este podera estar numa tabela "Hash function"
int index_da_tabela(char* string){
    char t=string[0];
    return t-'A';
}

//procura se existe um aluno na tabela com um determinado numero que é pasado a função
pAlunos procura_aluno_na_tabela_peloNumero(int numero, pAlunos* tabela){
    pAlunos temp;
    for (int i = 0; i < 26; ++i) {
        temp = tabela[i];
        while (temp->proximo!=NULL){
            if(temp->proximo->ficha_aluno.numero==numero)
                return temp;
            temp=temp->proximo;
        }
    }
    return NULL;
}

// recebe um ponteiro para um pAluno, cria um novo aluno com base no input do utilizador e acossia este ao pAluno extrior passado por referencia
int cria_ficha_para_novo_aluno(pAlunos* tabela, pAlunos* novo_aluno){
    pAlunos temp = (pAlunos) malloc(sizeof(noAluno));
    if(temp==NULL) return 1;
    if(inicializa_lista_de_depesas(&temp->ficha_aluno.lista_De_Despesas)==-1) return 1;

    char numero_de_estudante[8];
    char msg_a_pedir_numero_de_estudante[]="Input the student number: ";
    char msg_erro_numeroDeEstudante[]="ERROR: The number introduced is invalid.";
    int numero, controlo=0;
    while (controlo==0){
        valida_inputs(msg_a_pedir_numero_de_estudante, msg_erro_numeroDeEstudante, 8, numero_de_estudante, 4);
        sscanf(numero_de_estudante, "%d", &numero);
        if(procura_aluno_na_tabela_peloNumero(numero, tabela)==NULL)
            controlo=1;
        else {
            printf("ERROR: There is already a student with that number.\n\n");
        }
    }
    temp->ficha_aluno.numero=numero;

    char msg_a_pedir_nomeAluno[]="Input the student name: ";
    char msg_erro_nome_invalido[]="ERROR: Student name must start with a capital letter.";
    valida_inputs(msg_a_pedir_nomeAluno, msg_erro_nome_invalido, TAM, temp->ficha_aluno.nome, 5);

    char msg_pedir_saldo_inicial[]="Input student initial balance:";
    char msg_erro_saldo_invalido[]="ERROR: Invalid balance value.";
    char saldo[6];
    valida_inputs(msg_pedir_saldo_inicial, msg_erro_saldo_invalido, 6, saldo, 0);
    sscanf(saldo, "%f", &temp->ficha_aluno.saldo);

    char msg_a_pedir_data_de_nascimento[]="Input student birth date(DD/MM/YYYY):";
    char msg_data_nascimento_invalida[]="ERROR: Invalid date format.";
    char data_de_nascimento[11];
    valida_inputs(msg_a_pedir_data_de_nascimento, msg_data_nascimento_invalida, 11, data_de_nascimento, 1);
    sscanf(data_de_nascimento, "%d/%d/%d", &temp->ficha_aluno.data_nascimento.dia, &temp->ficha_aluno.data_nascimento.mes, &temp->ficha_aluno.data_nascimento.ano);

    char msg_a_pedir_ano_frequentado[]="Input student school year:";
    char msg_anoF_invalido[]="ERROR: Input a year between 10-12.";
    char ano_frequentado[3];
    valida_inputs(msg_a_pedir_ano_frequentado, msg_anoF_invalido, 3, ano_frequentado, 2);
    sscanf(ano_frequentado, "%d", &temp->ficha_aluno.ano);

    char msg_a_pedir_a_turma[]="Input student class:";
    char msg_turmaI_invalida[]="ERROR: Input a class between A-Z";
    char turma[2];
    valida_inputs(msg_a_pedir_a_turma, msg_turmaI_invalida, 2, turma, 3);
    temp->ficha_aluno.turma=turma[0];

    temp->proximo=NULL;
    *novo_aluno=temp;
    return 0;
}

// procura em uma tabela, tendo como referencia um determinado aluno, a possição antrior a esse aluno e postrior tendo como metodo de comparação precedencia em ordem alfabetica
void lugar_para_inserirAl(pAlunos* tabela, pAlunos* antrior, pAlunos* atual, pAlunos novo_elemento){
    *antrior=tabela[index_da_tabela(novo_elemento->ficha_aluno.nome)];
    *atual=tabela[index_da_tabela(novo_elemento->ficha_aluno.nome)]->proximo;
    while ((*atual)!=NULL && strcasecmp(novo_elemento->ficha_aluno.nome, (*atual)->ficha_aluno.nome)>=0){
        (*antrior)=(*atual);
        (*atual)=(*atual)->proximo;
    }
}

// insere um novo aluno em uma tabela tendo em cora em que lista é que este deve ficar e a posição dentro dessa lista
void insere_novoAl_naTabela(pAlunos* tabela, pAlunos novo_aluno){
    pAlunos antrior, atual;

    lugar_para_inserirAl(tabela,  &antrior, &atual, novo_aluno);
    novo_aluno->proximo=antrior->proximo;
    antrior->proximo=novo_aluno;
}

// montra na consola toda a informação sobre um aluno mostrando primeiro a sua ficha de aluno e de seguida a lista de despesas acossiada a este por ordem cronologica
void mostra_ficha_do_aluno(pAlunos aluno){
    printf("____________________Student Information__________________\n\n", aluno->ficha_aluno.nome, aluno->ficha_aluno.numero);
    printf("Name:%s\n"
           "Number:%d\n"
           "Class:%d %c\n"
           "Birth Date:%d/%d/%d\n"
           "Balance:%.2f\n", aluno->ficha_aluno.nome, aluno->ficha_aluno.numero,aluno->ficha_aluno.ano, aluno->ficha_aluno.turma,aluno->ficha_aluno.data_nascimento.dia, aluno->ficha_aluno.data_nascimento.mes, aluno->ficha_aluno.data_nascimento.ano, aluno->ficha_aluno.saldo);
    if(!verifica_se_a_lista_de_despesas_estaVazia(aluno->ficha_aluno.lista_De_Despesas)){
        pDespesas temp=aluno->ficha_aluno.lista_De_Despesas->proximo;
        printf("\n__Student expenses from %s:___\n\n", aluno->ficha_aluno.nome);
        while(temp!=NULL){
            printf("Date of the expense:%d/%d/%d \n", temp->ficha_despesa.Data.dia, temp->ficha_despesa.Data.mes, temp->ficha_despesa.Data.ano);
            printf("Value:%.2f\n", temp->ficha_despesa.valor);
            printf("Description:\n%s\n", temp->ficha_despesa.desc);
            temp=temp->proximo;
        }
    } else
        printf("\nStudent does not have any expenses.\n");
}

// menu de pesquisa de alunos pelo nome e numero que permite ao utilizador escolher um aluno dentro das possiveis opções se existirem
int usuario_procura_aluno(pAlunos* tabela, char* msg_a_preguntar_pelo_aluno, char* msg_aluno_nao_encontrado, char* msg_aluno_encontrado, pAlunos* aluno_antes){
    pAlunos aluno;
    int opcao, controlo=0;
    char op[2];
    char op_invalida[]="ERROR: Chose an option between 1 and 2.\n";
    while (controlo==0) {
        valida_inputs(msg_a_preguntar_pelo_aluno, op_invalida, 2, op, 4);
        sscanf(op, "%d", &opcao);
        if(opcao==1 || opcao==2){
            controlo=1;
        } else
            printf("%s\n", op_invalida);
    }

    if(opcao==1){
        char num[7];
        int numero;
        char pedir_numero_do_aluno[]="Input student number: ";
        char formato_invalido[]="ERROR: Invalid input.";
        valida_inputs(pedir_numero_do_aluno, formato_invalido, 7, num, 4);
        sscanf(num, "%d", &numero);
        aluno=procura_aluno_na_tabela_peloNumero(numero, tabela);
        *aluno_antes=aluno;
        if(aluno!=NULL) {
            printf("%s\n", msg_aluno_encontrado);
        }else {
            printf("%s\n", msg_aluno_nao_encontrado);
            return 2;
        }
    } else{

        char nome[TAM];
        pAlunos testar;
        int nElm=1;

        char formato_invalido_nome[]="ERROR: Write any string without numbers.";
        char pedir_nome_do_aluno[] = "Input student name/part of the student name:";
        valida_inputs(pedir_nome_do_aluno, formato_invalido_nome, TAM, nome, 6);
        pNoAluno* lista_auxiliar;
        if(inicializa_lista_pNoal(&lista_auxiliar)==1)return 1;


        if(opcao==2){
            for (int i = 0; i < 26; ++i) {
                testar = tabela[i];
                while (testar->proximo!=NULL){
                    if(strstr(testar->proximo->ficha_aluno.nome, nome)!=NULL){
                        nElm++;
                        pNoAluno *novo_elemento, *atual, *anterior;
                        if (cria_pNoal(&novo_elemento, testar) == 1) return 1;
                        procura_lugar_pNoal_ordemalpha(lista_auxiliar, &atual, &anterior, novo_elemento);
                        anterior->proximo = novo_elemento;
                        novo_elemento->proximo = atual;
                    }
                    testar=testar->proximo;
                }
            }
        }

        if(nElm==1){
            // If no student is found return 2
            return 2;
        }

        pNoAluno* temp=lista_auxiliar;
        int elm;
        controlo=0;
        printf("Students found:\n\n");
        for (int i = 0; i < nElm; ++i) {
            if(i==0)
                printf("%d-CANCEL\n", i);
            else{
                temp=temp->proximo;
                printf("%d-Name:%s N:%d;\n", i, temp->apontaPara->proximo->ficha_aluno.nome, temp->apontaPara->proximo->ficha_aluno.numero);
            }
        }
        printf("\n");
        char Opcao2[7];
        char pedir_opcao2[]="Input student option:\n"
                            "--\32";
        char opcao2_erro_invalida[]="ERROR: Invalid input.";
        while (controlo==0) {
            valida_inputs(pedir_opcao2, opcao2_erro_invalida, 7, Opcao2, 4);
            sscanf(Opcao2, "%d", &elm);
            if(elm>=0 && elm<nElm)
                controlo=1;
            else
                printf("ERROR: Invalid input.\n");

        }

        if(elm==0){
            //is none is chosen
            return 3;
        }

        temp=lista_auxiliar->proximo;
        for (int i = 1; i < elm; ++i) {
            temp=temp->proximo;
        }
        *aluno_antes=temp->apontaPara;
        lista_auxiliar= destroi_lista_pNoal(lista_auxiliar);
    }
    return 0;
}

/* Funções sobre pNoAluno */

// recebe um ponteiro para uma lista de pNoAluno* (lista auxiliar com ponteiros para pAlunos permite melhor economia de memoria), cria um header e acossia-o a lista ligada
int inicializa_lista_pNoal(pNoAluno** pLista){
    pNoAluno* temp= (pNoAluno*) malloc(sizeof(pNoAluno));
    if(temp==NULL){ return 1;}
    temp->proximo=NULL;
    *pLista=temp;
    return 0;
}

// verifica se a lista esta vazia
int verifica_vazia_pNoal(pNoAluno* lista){
    if(lista->proximo==NULL)
        return 1;
    return 0;
}

// recebe um ponteiro para um pNoAluno* e um ponteiro para o aluno, criado um novo pNoAluno que ira apontar para o aluno e ira ser acossiado ao pNoAluno* passado por referencia
int cria_pNoal(pNoAluno** pnovo_elemento, pAlunos apontaPara){
    pNoAluno* temp=(pNoAluno*)malloc(sizeof(pNoAluno));
    if(temp==NULL){ return 1;}
    temp->proximo=NULL;
    temp->apontaPara=apontaPara;
    *pnovo_elemento=temp;
    return 0;
}

// procura em uma lista de pNoAluno*, tendo como referencia um pNoAluno*, a possição antrior e postrior a esse elemento, tendo como metodo de comparação precedencia em ordem alfabetica
void procura_lugar_pNoal_ordemalpha(pNoAluno* lista, pNoAluno** atual, pNoAluno** anterior, pNoAluno* novo_elemento){
    *anterior=lista;
    *atual=lista->proximo;
    while ((*atual)!=NULL ){
        *anterior=(*anterior)->proximo;
        *atual=(*atual)->proximo;
    }
}

// procura em uma lista de pNoAluno*, tendo como referencia um pNoAluno*, a possição antrior e postrior a esse elemento, tendo como metodo de comparação o saldo dos alunos por ordem decrescente
void procura_lugar_pNoal_ordedecresscente(pNoAluno* lista, pNoAluno** atual, pNoAluno** anterior, pNoAluno* novo_elemento){
    *anterior=lista;
    *atual=lista->proximo;
    while ((*atual)!=NULL && novo_elemento->apontaPara->ficha_aluno.saldo <= (*atual)->apontaPara->ficha_aluno.saldo){
        (*anterior)=(*atual);
        (*atual)=(*atual)->proximo;
    }
}

// destroi a lista de pNoAluno* de forma a garatir que a memoria usada por esta possa ser reutilizada
pNoAluno* destroi_lista_pNoal(pNoAluno* lista){
    pNoAluno* temp;
    while (!verifica_vazia_pNoal(lista)){
        temp=lista;
        lista=lista->proximo;
        free(temp);
    }
    free(lista);
    return NULL;
}