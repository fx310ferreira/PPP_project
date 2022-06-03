#include "imports.h"

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

        case 4: // força a string a ser uma cadeia de digitos
            for (int i = 0; i < strlen(bufer); ++i) {
                if(bufer[i]<'0' || bufer[i]>'9')
                    return 0;
            }
            return 1;

        case 5: // valida Nome
            if(!(bufer[0]>='A' && bufer[0]<='Z'))
                return 0;
            for (int i = 1; i < strlen(bufer); ++i) {
                if((bufer[i]<'A'|| (bufer[i]>'Z' && bufer[i]<'a') || bufer[i]>'z') && bufer[i]!=' '){
                    return 0;
                }
            }
            return 1;

        case 6: // valida cadeia de strings com espacos

            for (int i = 0; i < strlen(bufer); ++i) {
                if(!( (bufer[i]>='a' && bufer[i]<='z') || (bufer[i]>='A' && bufer[i]<='Z') || bufer[i]==' '))
                    return 0;
            }
            return 1;

        default:
            return 1;
    }
}

int valida_inputs(char* msg_a_pedir_valor, char* msg_de_erro, int size_of_string, char* string, int parametro_de_comparacao){
    char* buffer= (char*)malloc(sizeof(char)*(size_of_string+1));
    if(buffer!=NULL){
        int controlo = 0;
        while (controlo == 0) {
            printf("%s", msg_a_pedir_valor);
            fseek(stdin, 0, 2);
            fgets(buffer, size_of_string + 1, stdin);
            printf("\n");
            if (buffer[strlen(buffer) - 1] == 10)
                buffer[strlen(buffer) - 1] = '\0';
            if (strlen(buffer) != size_of_string && filtrar(parametro_de_comparacao, buffer, size_of_string-1))
                controlo = 1;
            if (strlen(buffer) == size_of_string || !filtrar(parametro_de_comparacao, buffer, size_of_string-1)){
                printf("%s\n\n", msg_de_erro);
            }

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

/* Funções sobre ficheiros */

int load(pAlunos** ptabela){
    FILE * file = fopen("Save\\save.txt", "r");
    char string[400] = " ";
    criar_tabela(ptabela);
    pAlunos* tabela=*ptabela;
    pAlunos helper;
    while (fgets(string, 400, file) != NULL){
        char* token = strtok(string, ",");
        if(strcmp(token, "S") == 0){ // se for um aluno executa
            pAlunos new = (pAlunos) malloc(sizeof(noAluno));
            if(new==NULL) return 1;
            if(inicializa_lista_de_depesas(&new->ficha_aluno.lista_De_Despesas)==-1) return 1;
            helper = new;
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
            insere_novoAl_naTabela(tabela, new);
        }else{ // se  for despesa executa
            pDespesas nova_despesa = (pDespesas)malloc(sizeof(noDespesa));
            if(nova_despesa==NULL) return 1;
            token = strtok(NULL, ",");
            strcpy(nova_despesa->ficha_despesa.desc, token);
            token = strtok(NULL, ",");
            sscanf(token, "%d/%d/%d", &nova_despesa->ficha_despesa.Data.dia, &nova_despesa->ficha_despesa.Data.mes, &nova_despesa->ficha_despesa.Data.ano);
            token = strtok(NULL, ",");
            sscanf(token, "%f", &nova_despesa->ficha_despesa.valor);
            insere_despesa_auxiliar_load(helper, nova_despesa);
        }
    }
    fclose(file);
    return 0;
}

void save(pAlunos* tabela){
    FILE * file= fopen("Save\\save.txt", "w");
    pAlunos new;
    pDespesas despesa;
    for(int i=0; i<26; i++){
        new=tabela[i]->proximo;
        while (new != NULL){
            fprintf(file, "S,%d,%s,%d/%d/%d,%.2f,%d,%c\n", new->ficha_aluno.numero, new->ficha_aluno.nome,
                    new->ficha_aluno.data_nascimento.dia, new->ficha_aluno.data_nascimento.mes,
                    new->ficha_aluno.data_nascimento.ano, new->ficha_aluno.saldo, new->ficha_aluno.ano,
                    new->ficha_aluno.turma);
            despesa=new->ficha_aluno.lista_De_Despesas->proximo;
            while (despesa!=NULL){
                fprintf(file, "D,%s,%d/%d/%d,%.2f\n", despesa->ficha_despesa.desc, despesa->ficha_despesa.Data.dia,
                        despesa->ficha_despesa.Data.mes, despesa->ficha_despesa.Data.ano, despesa->ficha_despesa.valor);
                despesa=despesa->proximo;
            }
            new = new->proximo;
        }
    }
    fclose(file);
}

