//
// Created by fx310 on 11/05/2022.
//

#include "structs.h"

int filtrar(int parametro_de_comaparacao, char* bufer, int tamanho_maximo){
    switch (parametro_de_comaparacao) {
        case 0: //forca ao tamanho maximo da string
            if(strlen(bufer)==tamanho_maximo)
                return 1;
            else
                return 0;
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
        case 2:  // implica a string introduzida a ser uma cadeia de digitos
            if(strlen(bufer)==0)
                return 0;
            for (int i = 0; i < strlen(bufer); ++i) {
                if(bufer[i]<'0' || bufer[i]>'9')
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
        printf("%d\n", strlen(string));
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

int valida_caracters(char* string_introduzida){
    int controlo=1;

    for (int i = 0; i < 10; ++i) {
        if(i==2  || i==5){
            if(string_introduzida[i]!='/')
                controlo=0;
        }else {
            if('9'<string_introduzida[i])
                controlo=0;
            if('0'>string_introduzida[i])
                controlo=0;
        }
    }

    return controlo;
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

pDespesas desetroi_lista_de_despesas(pDespesas lista){
    pDespesas temp;
    while (!verifica_se_a_lista_de_despesas_estaVazia(lista)){
        temp=lista;
        lista=lista->proximo;
        free(temp);
    }
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
    valida_inputs(msg_a_pedir_valor_da_despesa, msg_valor_nValido, 7, valor_da_despesa, 2);
    sscanf(valor_da_despesa, "%d", &temp->ficha_despesa.valor);

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
