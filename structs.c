//
// Created by fx310 on 11/05/2022.
//

#include "structs.h"

int filtrar(int parametro_de_comaparacao, char* bufer, int tamanho_maximo){
    switch (parametro_de_comaparacao) {
        case 0: // valida floats
            if(strlen(bufer)==0)
                return 0;
            int controlo=0;
            for (int i = 0; i < strlen(bufer); ++i) {
                if(bufer[i]=='.'){
                    if(i==0 || i==strlen(bufer)-1)
                        return 0;
                    controlo++;
                    if(controlo>=2)
                        return 0;
                } else if(bufer[i]<'0' || bufer[i]>'9')
                    return 0;
            }
            return 1;

        case 1: //valida datas
            if(strlen(bufer)!=10)
                return 0;
            else{
                for (int i = 0; i < 10; ++i) {
                    if (i == 2 || i == 5) {
                        if (bufer[i] != '/')
                            return 0;
                    } else {
                        if (bufer[i] < '0' || bufer[i] > '9')
                            return 0;
                    }
                }
            }
            data data_a_validar;
            sscanf(bufer, "%d/%d/%d", &data_a_validar.dia, &data_a_validar.mes, &data_a_validar.ano);
            if(verifica_se_a_data_e_valida(&data_a_validar, 2000)==1)
                return 1;
            else
                return 0;

        case 2:  // valida ano escolar 10-12
            if(strlen(bufer)==0)
                return 0;
            for (int i = 0; i < strlen(bufer); ++i) {
                if(bufer[i]<'0' || bufer[i]>'9')
                    return 0;
            }
            int numero;
            sscanf(bufer, "%d", &numero);
            if(numero<10 || numero>12)
                return 0;
            return 1;

        case 3: // valida turma A-Z
            if(strlen(bufer)!=1)
                return 0;
            if(bufer[0]<'A' || bufer[0]>'Z')
                return 0;
            return 1;

        case 4: // força a string a ser uma cadeia de caracteres
            for (int i = 0; i < strlen(bufer); ++i) {
                if(bufer[i]<'0' || bufer[i]>'9')
                    return 0;
            }
            return 1;

        case 5: // Força o primeiro caracter ser letra em CAPS
            if(bufer[0]>='A' && bufer[0]<='Z')
                return 1;
            else
                return 0;

        default:
            return 1;
    }
}


int valida_inputs(char* msg_a_pedir_valor, char* msg_de_erro, int size_of_string, char* string, int parametro_de_comparacao){
    char* buffer= (char*)malloc(sizeof(char)*(size_of_string+1));
    if(buffer!=NULL){
        int controlo = 0;
        while (controlo == 0) {
            printf("%s\n", msg_a_pedir_valor);
            fseek(stdin, 0, 2);
            fgets(buffer, size_of_string + 1, stdin);
            if (buffer[strlen(buffer) - 1] == 10)
                buffer[strlen(buffer) - 1] = '\0';
            if (strlen(buffer) != size_of_string && filtrar(parametro_de_comparacao, buffer, size_of_string-1))
                controlo = 1;
            if (strlen(buffer) == size_of_string || !filtrar(parametro_de_comparacao, buffer, size_of_string-1))
                printf("%s\n", msg_de_erro);
        }
        strcpy_s(string, size_of_string, buffer);
        for (int i = size_of_string + 1; i < 0; --i) {
            free(buffer + i);
        }
        return 0;
    }
    return 1;
}


/*Datas*/

int verifica_mes_30d(data* pData){
    int var_de_controlo=0;
    int mes_com_30[]={4, 6, 9, 11};

    for (int* i = mes_com_30  ; i<=3+mes_com_30 ; i++) {
        if(*i==pData->mes)
            var_de_controlo=1;
    }
    return var_de_controlo;
}

int verifica_se_a_data_e_valida(data* pData, int ano_atual){
    if(pData->ano<ano_atual || pData->mes>12 || pData->mes<1 || pData->dia<1 || pData->dia>31)
        return 0;
    if(pData->mes==2){
        if( ((pData->ano)%4==0) && ( (((pData->ano)%100==0)&&((pData->ano)%400==0)) ||  ((pData->ano)%100!=0) )){
            if (pData->dia <= 29)
                return 1;
            else
                return 0;
        }
        if(pData->dia<=28)
            return 1;
        else
            return 0;

    }
    if(verifica_mes_30d(pData)){
        if(pData->dia<=30)
            return 1;
        else
            return 0;
    }
    return 1;
}


int compra_datas(data* chave, data* data1){
    if((chave->ano>data1->ano) || ((chave->ano==data1->ano) && (chave->mes > data1->mes)) || ((chave->ano==data1->ano) && (chave->mes==data1->mes) && (chave->dia > data1->dia)))
        return 1;
    if((data1->ano>chave->ano) || ((data1->ano==chave->ano) && (data1->mes > chave->mes)) || ((chave->ano==data1->ano) && (chave->mes==data1->mes) && (data1->dia > chave->dia)))
        return 0;
    return 2;
}


/* Funções sobre despesas */

int inicializa_lista_de_depesas(pDespesas* plista){ // -1 nao conseguiu alocar memoria
    noDespesa* temp= (noDespesa*) malloc(sizeof(noDespesa));
    if(temp!=NULL){
        temp->proximo=NULL; // sera necessario inicializar o header?
        *plista=temp;
        return 0;
    } else
        return -1;
}

int verifica_se_a_lista_de_despesas_estaVazia(pDespesas lista){
    if(lista->proximo==NULL)
        return 1;
    return 0;
}

pDespesas destroi_lista_de_despesas(pDespesas lista){
    pDespesas temp;
    while (!verifica_se_a_lista_de_despesas_estaVazia(lista)){
        temp=lista;
        lista=lista->proximo;
        free(temp);
    }
    free(lista);
    return NULL;
}

void procura_lugar_para_despesa(pDespesas lista, data* pData, pDespesas* anterior, pDespesas* atual){
    *anterior=lista;
    *atual=lista->proximo;
    while ((*atual)!=NULL && compra_datas(pData, &((*atual)->ficha_despesa.Data))>=1){
        *anterior=*atual;
        *atual=(*atual)->proximo;
    }
    if((*atual)!=NULL && compra_datas(&(*atual)->ficha_despesa.Data, pData)!=2)
        (*atual)=NULL;
}


int cria_despesa(pDespesas* pldespesa){
    noDespesa* temp=(noDespesa*) malloc(sizeof(noDespesa));
    if (temp == NULL) return 1;

    printf("Introduzir despesa: \n");

    char msg_pede_descricao[]="Introduza a descricao da despesa(maximo 99 caracters):";
    char msg_erro_input_invalido[]="A descricao introduzida foi considerada invalida.";
    valida_inputs(msg_pede_descricao, msg_erro_input_invalido, 100, temp->ficha_despesa.desc, 5);

    char data[11];
    char msg_pede_data[]="Introduza a data da despesa:";
    char msg_data_invalida[]="A data introduzida e invalida.";
    valida_inputs(msg_pede_data, msg_data_invalida, 11, data, 1);
    sscanf(data, "%d/%d/%d", &temp->ficha_despesa.Data.dia, &temp->ficha_despesa.Data.mes, &temp->ficha_despesa.Data.ano);

    char valor_da_despesa[7]; //0-999999 euros
    char msg_a_pedir_valor_da_despesa[]="Introduza o valor da despesa(0-999999 euros): ";
    char msg_valor_nValido[]="O valor introduzido nao e valido.";
    valida_inputs(msg_a_pedir_valor_da_despesa, msg_valor_nValido, 7, valor_da_despesa, 0);
    sscanf(valor_da_despesa, "%f", &temp->ficha_despesa.valor);

    temp->proximo=NULL;

    *pldespesa=temp;
    return 0;
}

void inser_despesa(pDespesas lista_De_Despesas){
    pDespesas nova_despesa, antrior, atual;
    cria_despesa(&nova_despesa);
    procura_lugar_para_despesa(lista_De_Despesas,&nova_despesa->ficha_despesa.Data, &antrior, &atual);
    nova_despesa->proximo=antrior->proximo;
    antrior->proximo=nova_despesa;
}


/* Funções sobre alunos */

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
    if(temp==NULL){ return 1; }
    if(inicializa_lista_de_depesas(&temp->ficha_aluno.lista_De_Despesas)==-1){ return 1; }

    char numero_de_estudante[8];
    char msg_a_pedir_numero_de_estudante[]="Introduza o numero de estudadente do aluno:";
    char msg_erro_numeroDeEstudante[]="O numero introduzido e invalido.";
    int numero, controlo=0;
    while (controlo==0){
        valida_inputs(msg_a_pedir_numero_de_estudante, msg_erro_numeroDeEstudante, 8, numero_de_estudante, 4);
        sscanf(numero_de_estudante, "%d", &numero);
        if(procura_aluno_na_tabela_peloNumero(numero, tabela)==NULL)
            controlo=1;
        else
            printf("%s\n", msg_erro_numeroDeEstudante);
    }
    temp->ficha_aluno.numero=numero;

    char msg_a_pedir_nomeAluno[]="Introduza o nome do aluno:";
    char msg_erro_nome_invalido[]="O nome introduzido e invalido.";
    valida_inputs(msg_a_pedir_nomeAluno, msg_erro_nome_invalido, TAM, temp->ficha_aluno.nome, 5);

    char msg_pedir_saldo_inicial[]="Introduza o saldo inicial do novo aluno:";
    char msg_erro_saldo_invalido[]="O saldo introduzido e invalido.";
    char saldo[7];
    valida_inputs(msg_pedir_saldo_inicial, msg_erro_saldo_invalido, 7, saldo, 0);
    sscanf(saldo, "%f", &temp->ficha_aluno.saldo);

    char msg_a_pedir_data_de_nascimento[]="Introduza a data de nascimento do novo aluno(fotmato DD/MM/AAAA):";
    char msg_data_nascimento_invalida[]="A data introduzida e invalida. ";
    char data_de_nascimento[11];
    valida_inputs(msg_a_pedir_data_de_nascimento, msg_data_nascimento_invalida, 11, data_de_nascimento, 1);
    sscanf(data_de_nascimento, "%d/%d/%d", &temp->ficha_aluno.data_nascimento.dia, &temp->ficha_aluno.data_nascimento.mes, &temp->ficha_aluno.data_nascimento.ano);

    char msg_a_pedir_ano_frequentado[]="Introduza o ano escolar frequentado pelo aluno:";
    char msg_anoF_invalido[]="O ano introduzido e invalido.";
    char ano_frequentado[3];
    valida_inputs(msg_a_pedir_ano_frequentado, msg_anoF_invalido, 3, ano_frequentado, 2);
    sscanf(ano_frequentado, "%d", &temp->ficha_aluno.ano);

    char msg_a_pedir_a_turma[]="Introduza a turma do aluno (formato A a Z sempre em maisculas):";
    char msg_turmaI_invalida[]="A formato introduzido e invalido.";
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

void procurar_lugar_na_fila(pAlunos fila, pAlunos* antrior, pAlunos* atual, pAlunos novo_elemento){
    *antrior=fila;
    *atual=fila->proximo;
    while ((*atual)!=NULL && strcasecmp(novo_elemento->ficha_aluno.nome, (*atual)->ficha_aluno.nome)>=0){
        (*antrior)=(*atual);
        (*atual)=(*atual)->proximo;
    }
}

void insere_novoAl_naFila(pAlunos fila, pAlunos novo_aluno){
    pAlunos antrior, atual;

    procurar_lugar_na_fila(fila,  &antrior, &atual, novo_aluno);
    novo_aluno->proximo=antrior->proximo;
    antrior->proximo=novo_aluno;
}

void mostra_ficha_do_aluno(pAlunos aluno){
    printf("Ficha do aluno %s numero %d:\n", aluno->ficha_aluno.nome, aluno->ficha_aluno.numero);
    printf("Nome: %s\n"
           "Numero: %d\n"
           "Turma: %c\n"
           "Data de nacimento: %d/%d/%d\n"
           "Saldo: %f\n", aluno->ficha_aluno.nome, aluno->ficha_aluno.numero, aluno->ficha_aluno.turma,aluno->ficha_aluno.data_nascimento.dia, aluno->ficha_aluno.data_nascimento.mes, aluno->ficha_aluno.data_nascimento.ano, aluno->ficha_aluno.saldo);
    if(!verifica_se_a_lista_de_despesas_estaVazia(aluno->ficha_aluno.lista_De_Despesas)){
        pDespesas temp=aluno->ficha_aluno.lista_De_Despesas->proximo;
        printf("\nLista de Despesa de %s:\n", aluno->ficha_aluno.nome);
        while(temp!=NULL){
            printf("Despesa do dia %d/%d/%d: \n", temp->ficha_despesa.Data.dia, temp->ficha_despesa.Data.mes, temp->ficha_despesa.Data.ano);
            printf("Descricao:\n%s\n", temp->ficha_despesa.desc);
            printf("Valor: %f\n\n", temp->ficha_despesa.valor);
            temp=temp->proximo;
        }
    } else
        printf("Este aluno nao tem nenhuma despesa reguistada.\n\n");
}

int usuario_procura_aluno(pAlunos* tabela, char* msg_a_preguntar_pelo_aluno, char* msg_aluno_nao_encontrado, char* msg_aluno_encontrado, pAlunos* aluno_antes){
    pAlunos aluno;
    int opcao, controlo=0;
    char op[2];
    char op_invalida[]="A opcao introduzida invalida.";
    while (controlo==0) {
        valida_inputs(msg_a_preguntar_pelo_aluno, op_invalida, 2, op, 4);
        sscanf(op, "%d", &opcao);
        if(opcao==1 || opcao==2 || opcao==3){
            controlo=1;
        } else
            printf("%s\n", op_invalida);
    }
    if(opcao==1){
        char num[7];
        int numero;
        char pedir_numero_do_aluno[]="Introduza o numero do aluno:";
        char formato_invalido[]="Formtato introduzido invalido.";
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

        char formato_invalido_nome[]="O formato introduzido invalido.";
        if(opcao==2){
            char pedir_nome_do_aluno[] = "Introduza o nome completo do aluno:";
            valida_inputs(pedir_nome_do_aluno, formato_invalido_nome, TAM, nome, 5);
        } else {
            char pedir_nome_do_aluno[] = "Introduza parte nome do aluno:";
            valida_inputs(pedir_nome_do_aluno, formato_invalido_nome, TAM, nome, 5);
        }

        pNoAluno* lista_auxiliar;
        if(inicializa_lista_pNoal(&lista_auxiliar)==1){ return 1;}

        if(opcao==2){
            testar = tabela[index_da_tabela(nome)];
            while (testar->proximo != NULL) {
                if (strcasecmp(testar->proximo->ficha_aluno.nome, nome) == 0) {
                    nElm++;
                    pNoAluno *novo_elemneto, *atual, *anterior;
                    if (cria_pNoal(&novo_elemneto, testar) == 1) { return 1; }
                    procura_lugar_pNoal_ordemalpha(lista_auxiliar, &atual, &anterior, novo_elemneto);
                    anterior->proximo = novo_elemneto;
                    novo_elemneto = atual;
                }
                testar = testar->proximo;
            }
        } else {
            for (int i = 0; i < 26; ++i) {
                testar = tabela[i];
                while (testar->proximo!=NULL){
                    if(strstr(testar->proximo->ficha_aluno.nome, nome)!=NULL){
                        nElm++;
                        pNoAluno *novo_elemneto, *atual, *anterior;
                        if (cria_pNoal(&novo_elemneto, testar) == 1) { return 1; }
                        procura_lugar_pNoal_ordemalpha(lista_auxiliar, &atual, &anterior, novo_elemneto);
                        anterior->proximo = novo_elemneto;
                        novo_elemneto = atual;
                    }
                    testar=testar->proximo;
                }
            }
        }

        pNoAluno* temp=lista_auxiliar;
        printf("\nEscolha uma das opcoes possiveis encontrada pelo programa se nao for nenhuma destas selecione a ultima opcao \"Nenhuma\"\n");
        for (int i = 0; i < nElm; ++i) {
            if(i==nElm-1)
                printf("%d- Nenhuma.\n", i);
            else{
                temp=temp->proximo;
                printf("%d- %s, n- %d ;\n", i, temp->apontaPara->proximo->ficha_aluno.nome, temp->apontaPara->proximo->ficha_aluno.numero);
            }
        }



        lista_auxiliar= destroi_lista_pNoal(lista_auxiliar);
    }
    return 0;
}

int eliminar_Aluno(pAlunos* tabela){
    pAlunos aluno_a_eleminar;

    return 0;
}


/* Funções sobre pNoAluno */

int inicializa_lista_pNoal(pNoAluno** pLista){
    pNoAluno* temp= (pNoAluno*) malloc(sizeof(pNoAluno));
    if(temp==NULL){ return 1;}
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
    while ((*atual)!=NULL && strcasecmp(novo_elemento->apontaPara->ficha_aluno.nome, (*atual)->apontaPara->ficha_aluno.nome)>=0){
        (*anterior)=(*atual);
        (*atual)=(*atual)->proximo;
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


/* Funções sobre ficheiros */

void load(pAlunos* plista_de_alunos){
    FILE * file = fopen("teste.txt", "r");
    char string[100] = " ";
    inicializa_lista_de_alunos(plista_de_alunos);
    pAlunos lista= (*plista_de_alunos);
    pAlunos helper = lista;
    while (fgets(string, 100, file) != NULL){
        char* token = strtok(string, ",");
        if(strcmp(token, "S") == 0){ // se for um aluno executa
            pAlunos new = (pAlunos) malloc(sizeof(noAluno));
            helper->proximo = new;
            new->proximo=NULL;
            token = strtok(NULL, ",");
            sscanf(token, "%d", &new->ficha_aluno.numero);
            token = strtok(NULL, ",");
            strcpy(new->ficha_aluno.nome, token);
            token = strtok(NULL, ",");
            sscanf(token, "%d/%d/%d", &new->ficha_aluno.data_nascimento.dia,&new->ficha_aluno.data_nascimento.mes,&new->ficha_aluno.data_nascimento.ano);
            token = strtok(NULL, ",");
            sscanf(token, "%f", &new->ficha_aluno.saldo);
            token = strtok(NULL, ",");
            sscanf(token, "%d", &new->ficha_aluno.ano);
            token = strtok(NULL, ",");
            sscanf(token, "%c", &new->ficha_aluno.turma);
            helper = new;
        }else{ // se  for despesa executa

        }
    }
    fclose(file);
}

void save(pAlunos* plista_de_alunos){
    FILE * file = fopen("teste.txt", "a");
    pAlunos new = (*plista_de_alunos)->proximo;
    while(new != NULL) {
        fprintf(file, "S,%d,%s,%d/%d/%d,%.2f,%d,%c\n", new->ficha_aluno.numero, new->ficha_aluno.nome,
                new->ficha_aluno.data_nascimento.dia, new->ficha_aluno.data_nascimento.mes,
                new->ficha_aluno.data_nascimento.ano, new->ficha_aluno.saldo, new->ficha_aluno.ano,
                new->ficha_aluno.turma);
        new = new->proximo;
    }
    fclose(file);
}

