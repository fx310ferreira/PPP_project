#include "imports.h"

int inicializa_lista_de_alunos(pAlunos* lista_de_alunos){
    pAlunos temp=(pAlunos) malloc(sizeof(noAluno));
    if(temp==NULL){ return 1; }
    temp->proximo=NULL;
    *lista_de_alunos = temp;
    return 0;
}

int criar_tabela(pAlunos** tabela){
    *tabela= (pAlunos*) malloc(sizeof(pAlunos)*26);
    if(*tabela==NULL){ return 1; }
    for (int i = 0; i < 26; ++i) {
        if(inicializa_lista_de_alunos(*tabela+i)==1)
            return 1;
    }
    return 0;
}

int verifica_lista_de_alunoVazia(pAlunos lista_de_aluno){
    if(lista_de_aluno->proximo==NULL)
        return 1;
    return 0;
}

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

void destroi_tabela(pAlunos* tabela){
    for (int i = 26; i < 0; --i) {
        tabela[i]= destroi_lista_de_alunos(tabela[i]);
        free(tabela+i);
    }
}

int index_da_tabela(char* string){
    char t=string[0];
    return t-'A';
}

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

void lugar_para_inserirAl(pAlunos* tabela, pAlunos* antrior, pAlunos* atual, pAlunos novo_elemento){
    *antrior=tabela[index_da_tabela(novo_elemento->ficha_aluno.nome)];
    *atual=tabela[index_da_tabela(novo_elemento->ficha_aluno.nome)]->proximo;
    while ((*atual)!=NULL && strcasecmp(novo_elemento->ficha_aluno.nome, (*atual)->ficha_aluno.nome)>=0){
        (*antrior)=(*atual);
        (*atual)=(*atual)->proximo;
    }
}

void insere_novoAl_naTabela(pAlunos* tabela, pAlunos novo_aluno){
    pAlunos antrior, atual;

    lugar_para_inserirAl(tabela,  &antrior, &atual, novo_aluno);
    novo_aluno->proximo=antrior->proximo;
    antrior->proximo=novo_aluno;
}

void mostra_ficha_do_aluno(pAlunos aluno){
    printf("____________________Student Information__________________\n\n", aluno->ficha_aluno.nome, aluno->ficha_aluno.numero);
    printf("Name:%s\n"
           "Number:%d\n"
           "Class:%d %c\n"
           "Birth Date:%d/%d/%d\n"
           "Balance:%.2f\n", aluno->ficha_aluno.nome, aluno->ficha_aluno.numero,aluno->ficha_aluno.ano, aluno->ficha_aluno.turma,aluno->ficha_aluno.data_nascimento.dia, aluno->ficha_aluno.data_nascimento.mes, aluno->ficha_aluno.data_nascimento.ano, aluno->ficha_aluno.saldo);
    if(!verifica_se_a_lista_de_despesas_estaVazia(aluno->ficha_aluno.lista_De_Despesas)){
        pDespesas temp=aluno->ficha_aluno.lista_De_Despesas->proximo;
        printf("\nStudent expenses from %s:\n\n", aluno->ficha_aluno.nome);
        while(temp!=NULL){
            printf("Date of the expense:%d/%d/%d \n", temp->ficha_despesa.Data.dia, temp->ficha_despesa.Data.mes, temp->ficha_despesa.Data.ano);
            printf("Value:%.2f\n", temp->ficha_despesa.valor);
            printf("Description:\n%s\n", temp->ficha_despesa.desc);
            temp=temp->proximo;
        }
    } else
        printf("\nStudent does not have any expenses.\n");
}

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

int inicializa_lista_pNoal(pNoAluno** pLista){
    pNoAluno* temp= (pNoAluno*) malloc(sizeof(pNoAluno));
    if(temp==NULL){ return 1;}
    temp->proximo=NULL;
    *pLista=temp;
    return 0;
}

int verifica_vazia_pNoal(pNoAluno* lista){
    if(lista->proximo==NULL)
        return 1;
    return 0;
}

int cria_pNoal(pNoAluno** pnovo_elemento, pAlunos apontaPara){
    pNoAluno* temp=(pNoAluno*)malloc(sizeof(pNoAluno));
    if(temp==NULL){ return 1;}
    temp->proximo=NULL;
    temp->apontaPara=apontaPara;
    *pnovo_elemento=temp;
    return 0;
}

void procura_lugar_pNoal_ordemalpha(pNoAluno* lista, pNoAluno** atual, pNoAluno** anterior, pNoAluno* novo_elemento){
    *anterior=lista;
    *atual=lista->proximo;
    while ((*atual)!=NULL ){
        *anterior=(*anterior)->proximo;
        *atual=(*atual)->proximo;
    }
}

void procura_lugar_pNoal_ordedecresscente(pNoAluno* lista, pNoAluno** atual, pNoAluno** anterior, pNoAluno* novo_elemento){
    *anterior=lista;
    *atual=lista->proximo;
    while ((*atual)!=NULL && novo_elemento->apontaPara->ficha_aluno.saldo <= (*atual)->apontaPara->ficha_aluno.saldo){
        (*anterior)=(*atual);
        (*atual)=(*atual)->proximo;
    }
}

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